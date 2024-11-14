#include "includes.h"

CMaterial::CMaterial(CShader* shader) {
	using ctor_with_shader_t = CMaterial * (__cdecl*)(CMaterial*, CShader*);
	static ctor_with_shader_t ctor_with_shader;

	if (!ctor_with_shader)
		ctor_with_shader = reinterpret_cast<ctor_with_shader_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Material"), xorstr_(".ctor"), 1));
	ctor_with_shader ? ctor_with_shader(this, shader) : nullptr;
}

CShader* CMaterial::Shader() {
	using get_shader_t = CShader * (__cdecl*)(CMaterial*);
	static get_shader_t get_shader;

	if (!get_shader)
		get_shader = reinterpret_cast<get_shader_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Material::get_shader")));
	return get_shader ? get_shader(this) : nullptr;
}

void CMaterial::Shader(CShader* shader) {
	using set_shader_t = void (__cdecl*)(CShader*);
	static set_shader_t set_shader;

	if (!set_shader)
		set_shader = reinterpret_cast<set_shader_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Material::set_shader")));
	return set_shader ? set_shader(shader) : (void)0;
}

CMaterial* CMaterial::CreateWithShader(CShader* shader) {
	using create_with_shader_t = CMaterial * (__cdecl*)(CMaterial*, CShader*);
	static create_with_shader_t create_with_shader;

	if (!create_with_shader)
		create_with_shader = reinterpret_cast<create_with_shader_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Material"), xorstr_("CreateWithShader")));
	return create_with_shader ? create_with_shader(reinterpret_cast<CMaterial*>(Pointer()), shader) : nullptr;
}

void CMaterial::SetColor(const char* name, SColor* value) {
	using set_color_t = void(__stdcall*)(CMaterial*, Il2CppString*, SColor*);
	static set_color_t set_color;

	if (!set_color)
		set_color = reinterpret_cast<set_color_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Material"), xorstr_("SetColor"), 2));
		//set_color = reinterpret_cast<set_color_t>(API::GetMethod(reinterpret_cast<uintptr_t*>(this), xorstr_("SetColor"), 2));
	return set_color ? set_color(this, memory::Il2Cpp::il2cpp_string_new(name), value) : (void)0;
}

void CMaterial::Color(SColor* value) {
	using set_color_t = void(__stdcall*)(CMaterial*, SColor*);
	static set_color_t set_color;

	if (!set_color)
		set_color = reinterpret_cast<set_color_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Material"), xorstr_("set_color"), 1));
	return set_color ? set_color(this, value) : (void)0;
}
