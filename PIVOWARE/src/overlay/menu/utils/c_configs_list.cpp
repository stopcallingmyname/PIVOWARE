#include "includes.h"

std::string& CConfigsList::GetFocusConfig() {
	auto result = std::string(xorstr_(""));

	if (m_vConfigsList.empty()) return result;

	const auto i = static_cast<int>(m_vConfigsList.size() - 1);

	m_iSelectedConfig = std::clamp(m_iSelectedConfig, 0, i);

	return m_vConfigsList[m_iSelectedConfig];
}

void CConfigsList::RefreshConfigsList() {
	if (!m_vConfigsList.empty())
		m_vConfigsList.clear();

	const auto path = g_pGVars->m_sConfig + xorstr_("\\*.json");

	WIN32_FIND_DATAA FindFileData;
	HANDLE hFileFind = FindFirstFileA(path.c_str(), &FindFileData);

	if (!hFileFind || hFileFind == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			m_vConfigsList.push_back(FindFileData.cFileName);

	} while (FindNextFileA(hFileFind, &FindFileData));

	FindClose(hFileFind);
}

void CConfigsList::SetFocusConfig(std::string name) {
	for (size_t i = 0; i < m_vConfigsList.size(); i++) {
		if (!m_vConfigsList[i].compare(name)) {
			m_iSelectedConfig = static_cast<int>(i);
			break;
		}
	}
}
