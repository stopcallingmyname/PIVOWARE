#include "includes.h"

CCamera* CCamera::Main() {
	using get_main_camera_t = CCamera * (__cdecl*)();
	static get_main_camera_t get_main_camera;

	if (!get_main_camera) 
		get_main_camera = reinterpret_cast<get_main_camera_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Camera"), xorstr_("get_main")));
	return get_main_camera ? get_main_camera() : nullptr;
}

float CCamera::Aspect() {
	using get_aspect_t = float(__cdecl*)();
	static get_aspect_t get_aspect;

	if (!get_aspect)
		get_aspect = (get_aspect_t)memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::get_aspect"));
	return get_aspect ? get_aspect() : 0.0f;
}

void CCamera::Aspect(float value) {
	using set_aspect_t = void(__cdecl*)(float);
	static set_aspect_t set_aspect;

	if (!set_aspect)
		set_aspect = (set_aspect_t)memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.RenderSettings::set_aspect"));
	return set_aspect ? set_aspect(value) : (void)0;
}

