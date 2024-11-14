#pragma once

class CConfigItem {
public:
	std::string m_sName;
	void* m_pPointer;
	std::string m_sType;

	CConfigItem(std::string name, void* pointer, std::string type);
};