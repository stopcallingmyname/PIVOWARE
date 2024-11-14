#include "includes.h"
#include "c_game_object.h"

CGameObject* CGameObject::Find(const char* name) {
	using find_game_object_t = CGameObject * (__stdcall*)(Il2CppString*);
	static find_game_object_t find_game_object;

	if (!find_game_object)
		find_game_object = reinterpret_cast<find_game_object_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("GameObject"), xorstr_("Find")));
	return find_game_object(memory::Il2Cpp::il2cpp_string_new(name));
}
