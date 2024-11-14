#include "includes.h"
#include "c_object.h"

Il2CppString* CObject::Name() {
	using get_name_t = Il2CppString*(__cdecl*)(CObject*);
	static get_name_t get_name;

	if (!get_name)
		get_name = reinterpret_cast<get_name_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.Object::get_name")));
	return get_name ? get_name(this) : nullptr;
}