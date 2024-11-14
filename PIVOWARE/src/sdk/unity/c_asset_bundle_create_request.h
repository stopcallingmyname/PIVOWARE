#pragma once

class CAssetBundle;

class CAssetBundleCreateRequest {
public:
	static auto* Pointer() {
		return API::GetClass(xorstr_("UnityEngine.AssetBundleModule.dll"), xorstr_("UnityEngine"), xorstr_("AssetBundleCreateRequest"));
	}

	CAssetBundle* AssetBundle();
};