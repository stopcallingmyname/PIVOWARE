#pragma once

class CAssetBundleManager {
public:
	CAssetBundleManager();
	~CAssetBundleManager();

	void LoadShaders();
	void LoadMaterials();

	CShader* GetShader(EShaderType type);
	CMaterial* GetMaterial(EMaterialType type);

private:
	void LoadAssetBundle();

	CAssetBundle* m_pAssetBundle;

	std::unordered_map<EShaderType, CShader*> m_mShaders;
	std::unordered_map<EMaterialType, CMaterial*> m_mMaterials;
};

extern std::unique_ptr<CAssetBundleManager> g_pAssetBundleManager;