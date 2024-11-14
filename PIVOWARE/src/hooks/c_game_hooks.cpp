#include "includes.h"

std::unique_ptr<CGameHooks> g_pGameHooks;

static CHookData main_gui_start, main_gui_update, main_menu_update, is_debugger_present;

BOOL WINAPI fdIsDebuggerPresent(VOID);

CGameHooks::CGameHooks() {
	HMODULE m_pKernel32 = GetModuleHandleA("kernel32.dll");
	FARPROC m_pIsDbgPresent = GetProcAddress(m_pKernel32, "IsDebuggerPresent");

	MAKE_HOOK(is_debugger_present, m_pIsDbgPresent, fdIsDebuggerPresent);

	MAKE_HOOK(main_gui_start, API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("MainGUI"), xorstr_("Start")), MainGUI_Start);
	if (!main_gui_start.IsHooked())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("main_gui_update -> FAILED"));

	MAKE_HOOK(main_gui_update, API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("MainGUI"), xorstr_("Update")), MainGUI_Update);
	if (!main_gui_update.IsHooked())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("main_gui_update -> FAILED"));

	MAKE_HOOK(main_menu_update, API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("MainMenu"), xorstr_("Update")), MainMenu_Update);
	if (!main_menu_update.IsHooked())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("main_menu_update -> FAILED"));
}

CGameHooks::~CGameHooks() {
	if (!m_mHooks.empty()) {
		this->m_mHooks.clear();
	}

	RESET_HOOK(main_gui_start);
	RESET_HOOK(main_gui_update);
	RESET_HOOK(main_menu_update);
}

void CGameHooks::RegisterHook(std::string eventName, std::string id, std::function<void()> function) {
	GameHook_t m_Hook = { id, function };
	/*CUtils::addlog("Registering hook for event: ", eventName.c_str());
	CUtils::addlog("Hook ID: ", id.c_str());*/
	this->m_mHooks[eventName].push_back(m_Hook);
}

//void CGameHooks::UnregisterHooks(std::string id) {
//	if (m_mHooks.empty()) return;
//	for (auto& m_Event : this->m_mHooks) {
//		int m_iPos = 0;
//
//		for (auto& m_Hook : m_Event.second) {
//			if (m_Hook.id == id)
//				m_Event.second.erase(m_Event.second.begin() + m_iPos);
//			m_iPos++;
//		}
//	}
//}

void CGameHooks::UnregisterHooks(std::string id) {
	if (m_mHooks.empty()) return;

	for (auto& m_Event : this->m_mHooks) {
		auto it = m_Event.second.begin();
		while (it != m_Event.second.end()) {
			if (it->id == id)
				it = m_Event.second.erase(it);
			else
				++it; 
		}
	}
}

//std::vector<GameHook_t> CGameHooks::GetHooks(std::string eventName) {
//	return this->m_mHooks[eventName];
//}

std::vector<GameHook_t> CGameHooks::GetHooks(std::string eventName) {
	auto it = m_mHooks.find(eventName);
	if (it != m_mHooks.end()) {
		return it->second;
	} else {
		//CUtils::addlog("Event not found: ", eventName.c_str());
		return {};
	}
}

BOOL WINAPI fdIsDebuggerPresent(VOID) { return FALSE; }

void CGameHooks::MainGUI_Start(uintptr_t* _inst) {
	if (g_pGameHooks.get() && g_pGameData.get()) {
		for (auto& func : g_pGameHooks->GetHooks(xorstr_("InGameStart")))
			func.func();
	}

	((original_method_t)main_gui_start.m_pOriginalFunction)(_inst);
}

void CGameHooks::MainGUI_Update(uintptr_t* _inst) {
	if (!g_pGVars->m_bIsInGame) {
		g_pGVars->m_bIsInGame = true;
	}

	if (g_pGameHooks.get() && g_pGameData.get()) {
		for (auto& func : g_pGameHooks->GetHooks(xorstr_("InGameUpdate")))
			func.func();
	}

	if (g_pVisuals.get()) 
		g_pVisuals->Update();

	((original_method_t)main_gui_update.m_pOriginalFunction)(_inst);
}

void CGameHooks::MainMenu_Update(uintptr_t* _inst) {
	if (g_pGVars->m_bIsInGame) {
		g_pGVars->m_bIsInGame = false;
	}

	if (g_pGameHooks.get() && g_pGameData.get()) {
		for (auto& func : g_pGameHooks->GetHooks(xorstr_("Update")))
			func.func();
	}

	if (g_pVisuals.get())
		g_pVisuals->InMenuUpdate();

	((original_method_t)main_menu_update.m_pOriginalFunction)(_inst);
}