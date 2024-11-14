#include "includes.h"

CAssetBundle* CAssetBundleCreateRequest::AssetBundle() {
	using get_asset_bundle_t = CAssetBundle * (__stdcall*)(CAssetBundleCreateRequest*);
	static get_asset_bundle_t get_asset_bundle;

	if (!get_asset_bundle)
		get_asset_bundle = reinterpret_cast<get_asset_bundle_t>(memory::Il2Cpp::il2cpp_resolve_icall(xorstr_("UnityEngine.AssetBundleCreateRequest::get_assetBundle")));
	//get_asset_bundle = reinterpret_cast<get_asset_bundle_t>(API::GetMethod(reinterpret_cast<uintptr_t*>(this), xorstr_("get_assetBundle")));
	return get_asset_bundle ? get_asset_bundle(this) : nullptr;
}
