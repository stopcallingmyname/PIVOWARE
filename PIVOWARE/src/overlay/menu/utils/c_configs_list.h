#pragma once

class CConfigsList {
public:
	std::vector<std::string> m_vConfigsList;

	int m_iSelectedConfig;
	int m_iSelectedFile;

	std::string& GetFocusConfig();

	void RefreshConfigsList();
	void SetFocusConfig(std::string name);
};