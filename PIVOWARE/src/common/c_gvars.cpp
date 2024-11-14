#include "includes.h"

std::unique_ptr<CGVars> g_pGVars;

std::string GetAppDataPath() {
	char* m_pBuf = nullptr;
	size_t m_lLen = 0;

	if (!_dupenv_s(&m_pBuf, &m_lLen, xorstr_("appdata")) && m_pBuf && strnlen_s(m_pBuf, MAX_PATH)) {
		std::string m_sSettingsPath;
		m_sSettingsPath.append(m_pBuf);
		free(m_pBuf);
		return m_sSettingsPath;
	}

	return std::string();
}

HWND GetWindowHandle() {
	HWND m_pData;

	EnumWindows([](HWND hWnd, LPARAM lParam) {
		HWND& m_pTdata = *(HWND*)lParam;

		DWORD dwProcessId;
		GetWindowThreadProcessId(hWnd, &dwProcessId);

		if (GetCurrentProcessId() != dwProcessId || !(!GetWindow(hWnd, GW_OWNER) && IsWindowVisible(hWnd)))
			return TRUE;

		m_pTdata = hWnd;
		return FALSE;

		}, (LPARAM)&m_pData);

	if (!m_pData || m_pData == INVALID_HANDLE_VALUE)
		m_pData = NULL;

	return m_pData;
}

CGVars::CGVars() {
	m_dbInjectedTime = static_cast<double>(clock());
	m_sAppData = GetAppDataPath();
	m_sLogFile = xorstr_("PIVOWARE.log");
	m_dwProcessId = GetCurrentProcessId();
	m_hWnd = GetWindowHandle();
}