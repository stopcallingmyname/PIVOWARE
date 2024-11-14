#include "includes.h"

DWORD WINAPI MainThread(LPVOID) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	if (!API::Initialize())
		TerminateProcess(GetCurrentProcess(), 0);

	g_pGVars->m_sConfig = xorstr_("\\PIVOWARE\\Configs\\");
	if (!std::filesystem::exists(g_pGVars->m_sConfig))
		std::filesystem::create_directories(g_pGVars->m_sConfig);

	m_pConfigManager = std::make_unique<CConfigManager>();
	CUtils::logger("m_pConfigManager [INIT]");
	m_pConfigManager->Setup();

	g_pGameHooks = std::make_unique<CGameHooks>();
	CUtils::logger("g_pGameHooks [INIT]");
	if (!g_pGameHooks.get())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("Failed to create game hooks\n"));

	g_pGameData = std::make_unique<CGameData>();
	CUtils::logger("g_pGameData [INIT]");

	g_pDirectX = std::make_unique<CDirectX>();
	CUtils::logger("g_pDirectX [INIT]");
	if (!g_pDirectX->Initialize())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("Failed to initialize DirectX\n"));

	return TRUE;
}

void CleanupResources() {
	g_pMenu.reset();
	g_pRender.reset();
	g_pFontManager.reset();
	g_pDirectX->Uninitialize();
	g_pDirectX.reset();
	g_pGameData.reset();
	g_pVisuals.reset();
	g_pAssetBundleManager.reset();
	g_pGameHooks.reset();
	m_pConfigManager.reset();
	g_pGVars.reset();

	API::Uninitialize();
	MH_Uninitialize();
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {

		if (::GetLastError() == ERROR_ALREADY_EXISTS) {
			TerminateProcess(GetCurrentProcess(), 0);
			return FALSE;
		}

		g_pGVars = std::make_unique<CGVars>();
		CUtils::logger("g_pGVars [INIT]");

		if (!g_pGVars->m_hWnd || g_pGVars->m_hWnd == INVALID_HANDLE_VALUE) {
			TerminateProcess(GetCurrentProcess(), 0);
			return FALSE;
		}

		g_pGVars->m_hModule = hInstance;

		if (MH_Initialize() != MH_OK) {
			TerminateProcess(GetCurrentProcess(), 0);
			return FALSE;
		}

		
#ifdef _DEBUG
#pragma message("Compiling in Debug mode.")
		CreateThread(NULL, 0, MainThread, hInstance, 0, NULL);
#else
#pragma message("Compiling in Release mode")
		MainThread(hInstance);
#endif

		return TRUE;
	}

	if (fdwReason == DLL_PROCESS_DETACH)
		CleanupResources();

	return FALSE;
}