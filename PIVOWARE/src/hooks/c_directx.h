#pragma once

#ifndef _HOOKS_DIRECTX_
#define _HOOKS_DIRECTX_

#include <d3d11.h>

class CDirectX {
public: 
	bool Initialize();
	void Uninitialize();

private:
	static ID3D11Device* g_pd3dDevice;
	static ID3D11DeviceContext* g_pd3dDeviceContext;
	static IDXGISwapChain* g_pSwapChain;
	static ID3D11RenderTargetView* g_mainRenderTargetView;
	static WNDPROC g_WndProc;
	static HWND g_hWnd;

	static std::uintptr_t* g_pSwapChainVtable;

	static void CreateRenderTargetView(IDXGISwapChain* SwapChain, ID3D11Texture2D* RenderTargetTexture = nullptr);
	static void GetImmediateContextFromSwapChain(IDXGISwapChain* SwapChain);

	static void CleanupDeviceD3D();
	static void CleanupRenderTarget();

	static LRESULT WINAPI WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	static HRESULT WINAPI hkPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);
	static std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)> oPresent;

	static HRESULT WINAPI hkResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static std::add_pointer_t<HRESULT WINAPI(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)> oResizeBuffers;

	static std::once_flag g_ImGuiIsInitialized;
};

extern std::unique_ptr<CDirectX> g_pDirectX;

#endif