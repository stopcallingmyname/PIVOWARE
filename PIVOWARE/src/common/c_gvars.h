#pragma once

class CGVars {
public:
	CGVars();

	WNDPROC			m_pWndProc;
	HMODULE			m_hModule;
	HWND			m_hWnd;
	DWORD			m_dwProcessId;

	bool			m_bIsUnloadingLibrary;
	bool			m_bIsGameHooked;
	bool            m_bIsInGame;

	double			m_dbInjectedTime;
	float			m_fCurTime;

	std::string     m_sAppData;
	std::string		m_sLogFile;
	std::string     m_sConfig;
};

extern std::unique_ptr<CGVars> g_pGVars;