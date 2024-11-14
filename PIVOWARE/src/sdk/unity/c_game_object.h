#pragma once

class CGameObject : public CObject {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("GameObject")); }

	static CGameObject* Find(const char* name);

	template<typename T>
	T* GetComponent();

	template<typename T>
	T* GetComponentInChildren(bool includeInactive = false);
};

template<typename T>
inline T* CGameObject::GetComponent() {
	using get_component_t = T * (__stdcall*)(CGameObject*, Il2CppReflectionType*);
	static get_component_t get_component;

	if (!get_component)
		get_component = reinterpret_cast<get_component_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("GameObject"), xorstr_("GetComponent"), 1));
	return get_component ? get_component(this, API::GetSystemType(reinterpret_cast<Il2CppClass*>(T::Pointer()))) : nullptr;
}

template<typename T>
inline T* CGameObject::GetComponentInChildren(bool includeInactive) {
	using get_component_in_children_t = T * (__stdcall*)(CGameObject*, Il2CppReflectionType*, bool);
	static get_component_in_children_t get_component_in_children;

	if (!get_component_in_children)
		get_component_in_children = reinterpret_cast<get_component_in_children_t>(API::GetMethod(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("GameObject"), xorstr_("GetComponentInChildren"), 1));
	return get_component_in_children ? get_component_in_children(this, API::GetSystemType(reinterpret_cast<Il2CppClass*>(T::Pointer())), includeInactive) : nullptr;
}
