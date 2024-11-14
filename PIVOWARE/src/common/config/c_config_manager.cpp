#include "includes.h"

std::unique_ptr<CConfigManager> m_pConfigManager;

void CConfigManager::Setup() {
	SetupAimbot();
	SetupVisuals();
	SetupMisc();
}

void CConfigManager::SetupAimbot() {

}

void CConfigManager::SetupVisuals() {
	// World
	SetupItem(&g_Cvars.visuals.world.enable, false, xorstr_("Visuals.World.Enable"));
	SetupItem(&g_Cvars.visuals.world.fog, true, xorstr_("Visuals.World.Fog"));
	SetupItem(&g_Cvars.visuals.world.skybox, 0, xorstr_("Visuals.World.Skybox"));
	SetupItem(&g_Cvars.visuals.world.wireframe_color, 4, xorstr_("Visuals.World.WireframeColor"));

	// Local
	SetupItem(&g_Cvars.visuals.local.enable, false, xorstr_("Visuals.Local.Enable"));
	SetupItem(&g_Cvars.visuals.local.aspectChanger.enable, false, xorstr_("Visuals.Local.AspectChanger.Enable"));
	//SetupItem(&g_Cvars.visuals.local.aspectChanger.value, , xorstr_("Visuals.Local.AspectChanger.Value"));
	SetupItem(&g_Cvars.visuals.local.fovChanger[0].enable, false, xorstr_("Visuals.Local.FovChanger[0].Enable"));
	//SetupItem(&g_Cvars.visuals.local.fovChanger[0].value, , xorstr_("Visuals.Local.FovChanger[0].Value"));
	SetupItem(&g_Cvars.visuals.local.fovChanger[0].enable, false, xorstr_("Visuals.Local.FovChanger[1].Enable"));
	//SetupItem(&g_Cvars.visuals.local.fovChanger[0].value, , xorstr_("Visuals.Local.FovChanger[1].Value"));
	SetupItem(&g_Cvars.visuals.local.chams_color, 4, xorstr_("Visuals.World.ChamsColor"));
}

void CConfigManager::SetupMisc() {

}

void CConfigManager::Load(std::string config) {
	if (config.empty()) {

#ifdef _DEBUG
		CUtils::logger(xorstr_("[event]: Failed to load config with name '%s'.\n"), xorstr_("NULL"));
#endif

		return;
	}

	if (config.find(xorstr_(".json")) == std::string::npos)
		config += xorstr_(".json");

	static auto find_item = [](std::vector< CConfigItem* > items, std::string name) -> CConfigItem* {
		for (int i = 0; i < (int)items.size(); i++)
			if (!items[i]->m_sName.compare(name))
				return items[i];

		return nullptr;
	};

	std::string folder = g_pGVars->m_sConfig, file = folder + config;
	if (!std::filesystem::exists(folder))
		std::filesystem::create_directories(folder);

	if (!std::filesystem::exists(file)) {

#ifdef _DEBUG
		CUtils::logger(xorstr_("> %s Config with this name was not found\n"), xorstr_(__FUNCTION__));
#endif

		return;
	}

	using json = nlohmann::json;

	std::string data;

	std::ifstream ifs;
	ifs.open(file + '\0');

	ifs >> data;
	ifs.close();

	if (data.empty())
		return;

	json allJson;
	allJson = json::parse(data);

	for (auto it = allJson.begin(); it != allJson.end(); ++it) {
		json j = *it;

		std::string name = j[xorstr_("name")];
		std::string type = j[xorstr_("type")];
		auto item = find_item(m_vConfigItems, name);

		if (item) {
			if (!type.compare(xorstr_("int")))
				*(int*)item->m_pPointer = j[xorstr_("value")].get<int>();
			else if (!type.compare(xorstr_("uint")))
				*(unsigned int*)item->m_pPointer = j[xorstr_("value")].get<unsigned int>();
			else if (!type.compare(xorstr_("float")))
				*(float*)item->m_pPointer = j[xorstr_("value")].get<float>();
			else if (!type.compare(xorstr_("bool")))
				*(bool*)item->m_pPointer = j[xorstr_("value")].get<bool>();
			else if (!type.compare(xorstr_("ImVec2"))) {
				std::vector<float> a;
				json ja = json::parse(j[xorstr_("value")].get<std::string>().c_str());

				for (json::iterator it = ja.begin(); it != ja.end(); ++it)
					a.push_back(*it);

				*(ImVec2*)item->m_pPointer = ImVec2(a[0], a[1]);
			} else if (!type.compare(xorstr_("vector<int>"))) {
				auto ptr = static_cast<std::vector <int>*> (item->m_pPointer);
				ptr->clear();

				json ja = json::parse(j[xorstr_("value")].get<std::string>().c_str());

				for (json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			} else if (!type.compare(xorstr_("vector<float>"))) {
				auto ptr = static_cast<std::vector <float>*> (item->m_pPointer);
				ptr->clear();

				json ja = json::parse(j[xorstr_("value")].get<std::string>().c_str());

				for (json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			} else if (!type.compare(xorstr_("vector<string>"))) {
				auto ptr = static_cast<std::vector <std::string>*> (item->m_pPointer);
				ptr->clear();

				json ja = json::parse(j[xorstr_("value")].get<std::string>().c_str());

				for (json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			} else if (!type.compare(xorstr_("string")))
				*(std::string*)item->m_pPointer = j[xorstr_("value")].get<std::string>();
		}
	}

#ifdef _DEBUG
	CUtils::logger(xorstr_("[event]: Loading config with name '%s'.\n"), config.c_str());
#endif
}

void CConfigManager::Save(std::string config) {
	if (config.empty()) {

#ifdef _DEBUG
		CUtils::logger(xorstr_("[event]: Failed to save config with name '%s'.\n"), xorstr_("NULL"));
#endif

		return;
	}

	if (config.find(xorstr_(".json")) == std::string::npos)
		config += xorstr_(".json");

	std::string folder = g_pGVars->m_sConfig, file = folder + config;
	if (!std::filesystem::exists(folder))
		std::filesystem::create_directories(folder);

	using json = nlohmann::json;

	json allJson;
	for (auto it : m_vConfigItems) {
		json j;

		j[xorstr_("name")] = it->m_sName;
		j[xorstr_("type")] = it->m_sType;

		if (!it->m_sType.compare(xorstr_("int")))
			j[xorstr_("value")] = (int)*(int*)it->m_pPointer;
		else if (!it->m_sType.compare(xorstr_("uint")))
			j[xorstr_("value")] = (unsigned int)*(unsigned int*)it->m_pPointer;
		else if (!it->m_sType.compare(xorstr_("float")))
			j[xorstr_("value")] = (float)*(float*)it->m_pPointer;
		else if (!it->m_sType.compare(xorstr_("bool")))
			j[xorstr_("value")] = (bool)*(bool*)it->m_pPointer;
		else if (!it->m_sType.compare(xorstr_("ImVec2"))) {
			auto v = *(ImVec2*)(it->m_pPointer);

			std::vector<float> a = { v.x, v.y };
			json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[xorstr_("value")] = ja.dump();
		} else if (!it->m_sType.compare(xorstr_("vector<int>"))) {
			auto& ptr = *(std::vector<int>*)(it->m_pPointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[xorstr_("value")] = ja.dump();
		} else if (!it->m_sType.compare(xorstr_("vector<float>"))) {
			auto& ptr = *(std::vector<float>*)(it->m_pPointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[xorstr_("value")] = ja.dump();
		} else if (!it->m_sType.compare(xorstr_("vector<string>"))) {
			auto& ptr = *(std::vector<std::string>*)(it->m_pPointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[xorstr_("value")] = ja.dump();
		} else if (!it->m_sType.compare(xorstr_("string")))
			j[xorstr_("value")] = (std::string) * (std::string*)it->m_pPointer;

		allJson.push_back(j);
	}

	std::string data;
	data = allJson.dump();

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << std::setw(4) << data << std::endl;
	ofs.close();

#ifdef _DEBUG
	CUtils::logger(xorstr_("[event]: Saving config with name '%s'.\n"), config.c_str());
#endif
}

void CConfigManager::Remove(std::string config) {
	if (config.empty()) {

#ifdef _DEBUG
		CUtils::logger(xorstr_("[event]: Failed to remove config with name '%s'.\n"), xorstr_("NULL"));
#endif

		return;
	}

	if (config.find(xorstr_(".json")) == std::string::npos)
		config += xorstr_(".json");

	std::string file = g_pGVars->m_sConfig + config;

#ifdef _DEBUG
	CUtils::logger(xorstr_("[event]: Removing config with name '%s'.\n"), config.c_str());
#endif

	if (std::filesystem::exists(file))
		std::filesystem::remove(file);
	else {
#ifdef _DEBUG
		CUtils::logger(xorstr_("[event]: Failed to remove config with name '%s'.\n"), config.c_str());
#endif
	}
}

void CConfigManager::AddItem(void* pointer, const char* name, const std::string& type) {
	m_vConfigItems.push_back(new CConfigItem(std::string(name), pointer, type));
}

void CConfigManager::SetupItem(int* pointer, int value, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("int"));
	*pointer = value;
}

void CConfigManager::SetupItem(unsigned int* pointer, unsigned int value, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("unit"));
	*pointer = value;
}

void CConfigManager::SetupItem(bool* pointer, bool value, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("bool"));
	*pointer = value;
}

void CConfigManager::SetupItem(float* pointer, float value, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("float"));
	*pointer = value;
}

void CConfigManager::SetupItem(ImVec2* pointer, ImVec2 value, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("ImVec2"));
	*pointer = value;
}

void CConfigManager::SetupItem(std::vector<int>* pointer, int size, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("vector<int>"));
	pointer->clear();

	for (int i = 0; i < size; i++)
		pointer->push_back(FALSE);
}

void CConfigManager::SetupItem(std::vector< float >* pointer, int size, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("vector<float>"));
	pointer->clear();

	for (int i = 0; i < size; i++)
		pointer->push_back(0.f);
}

void CConfigManager::SetupItem(std::vector<std::string>* pointer, std::vector<std::string> items, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("vector<string>"));
	pointer->clear();

	if (!items.empty()) {
		pointer->resize(items.size());
		for (auto& item : items)
			pointer->push_back(item);
	}
}

void CConfigManager::SetupItem(std::string* pointer, const std::string& value, size_t size, const std::string& name) {
	AddItem(pointer, name.c_str(), xorstr_("string"));
	pointer->clear();
	*pointer = value;
	if (size == -1)
		pointer->resize(value.size());
	else
		pointer->resize(size);
}
