#include "includes.h"

void CRenderSettings::Reset() {
	using reset_t = void(__cdecl*)();
	static reset_t _il2cpp_icall_func;

	if (!_il2cpp_icall_func)
		_il2cpp_icall_func = reinterpret_cast<reset_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::Reset")));
	return _il2cpp_icall_func ? _il2cpp_icall_func() : (void)0;
}

void CRenderSettings::Fog(bool value) {
	using set_fog_t = void(__cdecl*)(bool);
	static set_fog_t set_fog;

	if (!set_fog)
		set_fog = reinterpret_cast<set_fog_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::set_fog")));
	return set_fog ? set_fog(value) : (void)0;
}

CMaterial* CRenderSettings::Skybox() {
	using get_skybox_t = CMaterial * (__cdecl*)();
	static get_skybox_t get_skybox;

	if (!get_skybox)
		get_skybox = reinterpret_cast<get_skybox_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::get_skybox")));
	return get_skybox ? get_skybox() : nullptr;
}

void CRenderSettings::Skybox(CMaterial* value) {
	using set_skybox_t = void (__cdecl*)(CMaterial*);
	static set_skybox_t set_skybox;

	if (!set_skybox)
		set_skybox = reinterpret_cast<set_skybox_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::set_skybox")));
	return set_skybox ? set_skybox(value) : (void)0;
}
