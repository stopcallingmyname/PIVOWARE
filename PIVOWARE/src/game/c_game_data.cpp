#include "includes.h"

std::unique_ptr<CGameData> g_pGameData;

CGameData::CGameData() {
	if (g_pGameHooks.get()) {
		g_pGameHooks->RegisterHook(xorstr_("InGameStart"), xorstr_("GameUtils"), [&] { this->Start(); });
		g_pGameHooks->RegisterHook(xorstr_("InGameUpdate"), xorstr_("GameUtils"), [&] { this->Update(); });
	}

	g_pAssetBundleManager = std::make_unique<CAssetBundleManager>();
	CUtils::logger("g_pAssetBundleManager [INIT]");
	g_pVisuals = std::make_unique<CVisuals>();
	CUtils::logger("g_pVisuals [INIT]");
}

CGameData::~CGameData() {
	if (g_pGameHooks.get())
		g_pGameHooks->UnregisterHooks(xorstr_("GameUtils"));
}

void CGameData::Start() {
	if (g_pAssetBundleManager.get()) {
		g_pAssetBundleManager->LoadShaders();
		CUtils::logger("[Manager]: Shaders Loaded");
		g_pAssetBundleManager->LoadMaterials();
		CUtils::logger("[Manager]: Materials Loaded");
	}
}

void CGameData::Update() {
	if (IsReady()) {
	}
}

bool CGameData::IsReady() {
	return g_pGVars->m_bIsInGame && CClient::Instance();
}
