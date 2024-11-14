#include "includes.h"

std::unique_ptr<CDirectX> g_pDirectX;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND Window, UINT MSG_TYPE, WPARAM WPARAM, LPARAM LPARAM);

ID3D11Device* CDirectX::g_pd3dDevice = NULL;
ID3D11DeviceContext* CDirectX::g_pd3dDeviceContext = NULL;
IDXGISwapChain* CDirectX::g_pSwapChain = NULL;
ID3D11RenderTargetView* CDirectX::g_mainRenderTargetView = NULL;
WNDPROC CDirectX::g_WndProc = NULL;
HWND CDirectX::g_hWnd = NULL;

std::uintptr_t* CDirectX::g_pSwapChainVtable = nullptr;

std::once_flag CDirectX::g_ImGuiIsInitialized;

std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)> CDirectX::oPresent = NULL;
std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)> CDirectX::oResizeBuffers = NULL;

LRESULT WINAPI CDirectX::WndProc(HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam) {

	if (Msg == WM_KEYDOWN && wParam == VK_INSERT)
		g_pMenu->Toggle();

	ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wParam, lParam);

	if (g_pMenu->IsOpened()) {
		if ((GImGui->IO.WantCaptureMouse && (Msg == WM_LBUTTONDOWN || Msg == WM_LBUTTONUP || Msg == WM_RBUTTONDOWN || Msg == WM_RBUTTONUP || Msg == WM_MBUTTONDOWN || Msg == WM_MBUTTONUP || Msg == WM_MOUSEWHEEL || Msg == WM_MOUSEMOVE))
			|| (GImGui->IO.WantCaptureKeyboard && (Msg == WM_KEYDOWN || Msg == WM_SYSKEYDOWN || Msg == WM_KEYUP || Msg == WM_SYSKEYUP))) {
			if ((Msg == WM_KEYUP || Msg == WM_SYSKEYUP) && (wParam < 256))
				return CallWindowProc(g_WndProc, hWnd, Msg, wParam, lParam);
			return true;
		}
	}
	return CallWindowProc(g_WndProc, hWnd, Msg, wParam, lParam);
}

HRESULT WINAPI CDirectX::hkPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
	std::call_once(g_ImGuiIsInitialized, [&]() {

		GetImmediateContextFromSwapChain(SwapChain);
		CreateRenderTargetView(SwapChain);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.IniFilename = NULL;
		io.LogFilename = NULL;

		// Setup ImGui style
		ImGuiStyle* style = &ImGui::GetStyle();
		style->AntiAliasedFill = true;
		style->AntiAliasedLines = true;
		style->WindowPadding = ImVec2(0, 0);
		style->ItemSpacing = ImVec2(10, 10);
		style->ScrollbarSize = 10.f;

		// Setup ImGui config
		ImFontConfig config;
		//config.RasterizerMultiply = 1.125f;

		g_pFontManager = std::make_unique<CFontManager>();
		CUtils::logger("g_pFontManager [INIT]");
		g_pFontManager->AddFontFromMemory("Lexend-Bold", lexend_bold_data, sizeof(lexend_bold_data), 17, 25);
		g_pFontManager->AddFontFromMemory("Lexend-Regular", lexend_regular_data, sizeof(lexend_regular_data), 14, 25);
		g_pFontManager->AddFontFromMemory("Icomoon-Widget", icomoon_widget_data, sizeof(icomoon_widget_data), 1, 25);
		g_pFontManager->AddFontFromMemory("Icomoon", icomoon_data, sizeof(icomoon_data), 1, 25);

		g_pRender = std::make_unique<CRender>();
		CUtils::logger("g_pRender [INIT]");
		g_pMenu = std::make_unique<CMenu>();
		CUtils::logger("g_pMenu [INIT]");

		ImGui_ImplWin32_Init(g_hWnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

		if (!g_WndProc)
			g_WndProc = WNDPROC(SetWindowLongPtrA(g_hWnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc));
		});

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	g_pRender->RenderScene([] {
		if (g_pVisuals.get())
			g_pVisuals->Overlay();

		g_pMenu->Draw();
		//g_pMenu->Watermark(g_pMenu->m_sTitle, xorstr_("stopcallingmyname"), "47ms"); crash prob due to fps

		/*if (g_Cvars.settings.speclist) {
			g_pMenu->SpectatorList();
		}*/

		});

	ImGui::EndFrame();

	ImGui::Render();
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(SwapChain, SyncInterval, Flags);
}

HRESULT WINAPI CDirectX::hkResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	g_mainRenderTargetView->Release();
	g_mainRenderTargetView = nullptr;

	const HRESULT result = oResizeBuffers(SwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	CreateRenderTargetView(SwapChain);

	return result;
}

bool CDirectX::Initialize() {
	g_hWnd = g_pGVars->m_hWnd;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.Windowed = true;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	sd.BufferDesc.Width = 1;
	sd.BufferDesc.Height = 1;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK) {
		CUtils::logger(xorstr_("> %s: failed to create device D3D11\n"), xorstr_(__FUNCTION__));
		return FALSE;
	}

	g_pSwapChainVtable = reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t*>(g_pSwapChain)[0]);

	if (MH_CreateHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[8]), &hkPresent, reinterpret_cast<LPVOID*>(&oPresent)) != MH_OK) {
		CUtils::logger(xorstr_("> %s: failed to create hook on VTable 0x8\n"), xorstr_(__FUNCTION__));
		return FALSE;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[13]), &hkResizeBuffers, reinterpret_cast<LPVOID*>(&oResizeBuffers)) != MH_OK) {
		CUtils::logger(xorstr_("> %s: failed to create hook on VTable 0xD\n"), xorstr_(__FUNCTION__));
		return FALSE;
	}

	if (MH_EnableHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[8])) != MH_OK) {
		CUtils::logger(xorstr_("> %s: failed to enable on VTable 0x8\n"), xorstr_(__FUNCTION__));
		return FALSE;
	}

	if (MH_EnableHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[13])) != MH_OK) {
		CUtils::logger(xorstr_("> %s: failed to enable on VTable 0xD\n"), xorstr_(__FUNCTION__));
		return FALSE;
	}

	g_pGVars->m_bIsGameHooked = true;

	return TRUE;
}

void CDirectX::Uninitialize() {
	g_pd3dDevice->Release();
	g_pd3dDeviceContext->Release();
	g_pSwapChain->Release();

	MH_DisableHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[8]));
	MH_DisableHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[13]));
	MH_RemoveHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[8]));
	MH_RemoveHook(reinterpret_cast<LPVOID>(g_pSwapChainVtable[13]));

	SetWindowLongPtrA(g_pGVars->m_hWnd, GWLP_WNDPROC, (LONG_PTR)g_WndProc);

	g_pGVars->m_bIsGameHooked = false;
}

void CDirectX::CreateRenderTargetView(IDXGISwapChain* SwapChain, ID3D11Texture2D* RenderTargetTexture) {
	if (SUCCEEDED(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&RenderTargetTexture)))) {
		g_pd3dDevice->CreateRenderTargetView(RenderTargetTexture, nullptr, &g_mainRenderTargetView);
		RenderTargetTexture->Release();
	}
}

void CDirectX::GetImmediateContextFromSwapChain(IDXGISwapChain* SwapChain) {
	if (SUCCEEDED(SwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<LPVOID*>(&g_pd3dDevice))))
		g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
}

void CDirectX::CleanupDeviceD3D() {
	CleanupRenderTarget();
	if (g_pSwapChain)
		g_pSwapChain->Release(); g_pSwapChain = NULL;

	if (g_pd3dDeviceContext)
		g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL;

	if (g_pd3dDevice)
		g_pd3dDevice->Release(); g_pd3dDevice = NULL;
}

void CDirectX::CleanupRenderTarget() {
	if (g_mainRenderTargetView)
		g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL;
}