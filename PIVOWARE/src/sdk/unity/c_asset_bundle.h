#pragma once

class CAssetBundle : public CObject {
public:
	static auto* Pointer() {
		return API::GetClass(xorstr_("UnityEngine.AssetBundleModule.dll"), xorstr_("UnityEngine"), xorstr_("AssetBundle"));
	}

	template<typename T>
	T* LoadAsset(const char* name);
	void Unload(bool unloadAllLoadedObjects);

	static CAssetBundleCreateRequest* LoadFromMemoryAsync(const void* data);
	static CAssetBundle* LoadFromMemory(array<struct byte*>* data);
};

template<typename T>
inline T* CAssetBundle::LoadAsset(const char* name) {
	using load_asset_t = T*(__stdcall*)(CAssetBundle*, Il2CppString*, Il2CppReflectionType*);
	static load_asset_t load_asset;

	if (!load_asset)
		load_asset = reinterpret_cast<load_asset_t>(API::GetMethod(xorstr_("UnityEngine.AssetBundleModule.dll"), xorstr_("UnityEngine"), xorstr_("AssetBundle"), xorstr_("LoadAsset"), 2));
	return load_asset ? load_asset(this, memory::Il2Cpp::il2cpp_string_new(name), API::GetSystemType(reinterpret_cast<Il2CppClass*>(T::Pointer()))) : nullptr;
}
