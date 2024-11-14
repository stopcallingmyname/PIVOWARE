#include "includes.h"

void CAssetBundle::Unload(bool unloadAllLoadedObjects) {
	using unload_t = void (__stdcall*)(CAssetBundle*, bool);
	static unload_t unload;

	if (!unload)
		unload = reinterpret_cast<unload_t>(API::GetMethod(xorstr_("UnityEngine.AssetBundleModule.dll"), xorstr_("UnityEngine"), xorstr_("AssetBundle"), xorstr_("Unload"), 1));
	return unload ? unload(this, unloadAllLoadedObjects) : (void)0;
}

CAssetBundleCreateRequest* CAssetBundle::LoadFromMemoryAsync(const void* data) {
	using load_from_memory_async_t = CAssetBundleCreateRequest * (__stdcall*)(const void*);
	static load_from_memory_async_t load_from_memory_async;

	if (!load_from_memory_async)
		load_from_memory_async = reinterpret_cast<load_from_memory_async_t>(API::GetMethod(xorstr_("UnityEngine.AssetBundleModule.dll"), xorstr_("UnityEngine"), xorstr_("AssetBundle"), xorstr_("LoadFromMemoryAsync"), 1));
	return load_from_memory_async ? load_from_memory_async(memory::Il2Cpp::il2cpp_array_new(API::GetClass("mscorlib.dll", "System", "Byte"), sizeof(data))) : nullptr;
}

CAssetBundle* CAssetBundle::LoadFromMemory(array<struct byte*>* data) {
	using load_from_memory_t = CAssetBundle * (__stdcall*)(array<struct byte*>*, uint32_t);
	static load_from_memory_t load_from_memory;

	if (!load_from_memory)
		load_from_memory = reinterpret_cast<load_from_memory_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.AssetBundle::LoadFromMemory_Internal")));
	return load_from_memory ? load_from_memory(data, 0) : nullptr;
}