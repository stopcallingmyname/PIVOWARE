#include "includes.h"
#include "c_shader.h"

CShader* CShader::Find(const char* name) {
	using find_shader_t = CShader * (__stdcall*)(Il2CppString*);
	static find_shader_t find_shader;

	if (!find_shader)
		find_shader = reinterpret_cast<find_shader_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Shader"), xorstr_("Find")));
	return find_shader(memory::Il2Cpp::il2cpp_string_new(name));
}
