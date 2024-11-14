#pragma once

class CGameHooks {
public:
	CGameHooks();
	~CGameHooks();

	void RegisterHook(std::string eventName, std::string id, std::function<void()> func);
	void UnregisterHooks(std::string id);

	std::vector<GameHook_t> GetHooks(std::string eventName);

private:
	std::map<std::string, std::vector<GameHook_t>> m_mHooks;

	typedef void(*original_method_t)(void*);

	static void MainGUI_Start(uintptr_t* _inst);
	static void MainGUI_Update(uintptr_t* _inst);
	static void MainMenu_Update(uintptr_t* _inst);
};

extern std::unique_ptr<CGameHooks> g_pGameHooks;