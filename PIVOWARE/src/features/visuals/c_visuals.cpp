#include "includes.h"

std::unique_ptr<CVisuals> g_pVisuals;

static CHookData weapon_system_get_cursor, weapon_system_get_cursor_under_ray;

CVisuals::CVisuals() : m_pDrawWorld(std::make_unique<CDrawWorld>()), m_pDrawLocal(std::make_unique<CDrawLocal>()) {
	CUtils::logger("m_pDrawWorld [INIT]");

	MAKE_HOOK(weapon_system_get_cursor, API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("WeaponSystem"), xorstr_("GetCursor")), GetCursor);
	if (!weapon_system_get_cursor.IsHooked())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("weapon_system_get_cursor -> [FAILED]"));

	MAKE_HOOK(weapon_system_get_cursor_under_ray, API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("WeaponSystem"), xorstr_("GetCursorUnderRay")), GetCursorUnderRay);
	if (!weapon_system_get_cursor_under_ray.IsHooked())
		CUtils::addlogterminate(xorstr_(__FUNCTION__), xorstr_("weapon_system_get_cursor_under_ray -> [FAILED]"));
}

CVisuals::~CVisuals() {
	m_pDrawLocal.reset();
	m_pDrawWorld.reset();

	RESET_HOOK(weapon_system_get_cursor);
	RESET_HOOK(weapon_system_get_cursor_under_ray);
}

void CVisuals::Overlay() {
	m_pDrawLocal->Overlay();
}

void CVisuals::Update() {
	if (!CCamera::Main())
		return;

	if (!g_pGameData->IsReady())
		return;

	m_pDrawWorld->Update();
}

void CVisuals::OnDestroy() {}

void CVisuals::InMenuUpdate() {
	static bool m_bActive = false;

	if (g_Cvars.visuals.local.enable) {
		m_bActive = true;

		CGameObject* m_pTrooper = CGameObject::Find("trooper");
		CRenderer* m_pSkinnedMeshRenderer = m_pTrooper->GetComponent<CSkinnedMeshRenderer>();
		static CShader* m_pShader = nullptr;
		CMaterial* m_pChams = nullptr;

		if (!m_pShader)
			m_pShader = CShader::Find("GUI/Text Shader");

		if (!m_pChams)
			m_pChams = new CMaterial(m_pShader);


		if (m_pSkinnedMeshRenderer && m_pChams) {
			SColor m_pChamsColor = SColor(g_Cvars.visuals.local.chams_color);
			m_pChams->Color(&m_pChamsColor);
			m_pSkinnedMeshRenderer->Material(m_pChams);
		} 
	}
}

void CVisuals::FovChanger() {}

void CVisuals::AspectChanger() {}

CVector3* CVisuals::GetCursor(CVector3* retstr, void* _inst, bool inside, int32_t radius) {
	if (g_Cvars.visuals.local.shootig_through_walls) {
		CUtils::logger("GetCursor->nullptr");
		retstr->Init(0.f, 0.f, 0.f);
		return retstr;
	}
	//CUtils::logger("GetCursor->[HOOK]: inside->%d, radius->%d", inside, radius);
	return ((weapon_system_get_cursor_t)weapon_system_get_cursor.m_pOriginalFunction)(retstr, _inst, inside, radius);
}

CVector3* CVisuals::GetCursorUnderRay(CVector3* retstr, void* _inst, bool inside, int32_t radius, void* ray) {
	if (g_Cvars.visuals.local.shootig_through_walls) {
		CUtils::logger("GetCursorUnderRay->nullptr");
		return NULL;
	}
	//CUtils::logger("GetCursorUnderRay->[HOOK]: inside->%d, radius->%d", inside, radius);
	((weapon_system_get_cursor_under_ray_t)weapon_system_get_cursor.m_pOriginalFunction)(retstr, _inst, inside, radius, ray);
}
