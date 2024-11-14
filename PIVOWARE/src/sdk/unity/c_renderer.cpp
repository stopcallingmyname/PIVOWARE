#include "includes.h"

void CRenderer::Enabled(bool value) {
	using enabled_t = void (__stdcall*)(CRenderer*, bool);
	static enabled_t enabled;

	if (!enabled)
		enabled = reinterpret_cast<enabled_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Renderer"), xorstr_("set_enabled")));
	return enabled ? enabled(this, value) : (void)0;
}

bool CRenderer::Enabled() {
	using enabled_t = bool (__stdcall*)(CRenderer*);
	static enabled_t enabled;

	if (!enabled)
		enabled = reinterpret_cast<enabled_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Renderer"), xorstr_("get_enabled")));
	return enabled ? enabled(this) : false;
}

CMaterial* CRenderer::Material() {
	using get_material_t = CMaterial* (__stdcall*)(CRenderer*);
	static get_material_t get_material;

	if (!get_material)
		get_material = reinterpret_cast<get_material_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Renderer"), xorstr_("GetMaterial")));
	return get_material ? get_material(this) : nullptr;
}

void CRenderer::Material(CMaterial* material) {
	using set_material_t = void (__stdcall*)(CRenderer*, CMaterial*);
	static set_material_t set_material;

	if (!set_material)
		set_material = reinterpret_cast<set_material_t>(memory::get_base_address() + 0x25C0740);
		//set_material = reinterpret_cast<set_material_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Renderer"), xorstr_("set_material"), 1));
	return set_material ? set_material(this, material) : (void)0;
}
