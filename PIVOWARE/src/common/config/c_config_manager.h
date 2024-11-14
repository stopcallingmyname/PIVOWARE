#pragma once

class CConfigManager {
public:
	void Setup();

	void Load(std::string config);
	void Save(std::string config);
	void Remove(std::string config);

	std::vector <CConfigItem*> m_vConfigItems;
private:
	void AddItem(void* pointer, const char* name, const std::string& type);
	void SetupItem(int*, int, const std::string&);
	void SetupItem(unsigned int*, unsigned int, const std::string&);
	void SetupItem(bool*, bool, const std::string&);
	void SetupItem(float*, float, const std::string&);
	void SetupItem(ImVec2*, ImVec2, const std::string&);
	void SetupItem(std::vector< int >*, int, const std::string&);
	void SetupItem(std::vector< float >*, int, const std::string&);
	void SetupItem(std::vector< std::string >*, std::vector< std::string >, const std::string&);
	void SetupItem(std::string*, const std::string&, size_t, const std::string&);

	void SetupAimbot();
	void SetupVisuals();
	void SetupMisc();
};

extern std::unique_ptr<CConfigManager> m_pConfigManager;

