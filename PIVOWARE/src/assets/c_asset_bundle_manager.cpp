#include "includes.h"

std::unique_ptr<CAssetBundleManager> g_pAssetBundleManager;

//CAssetBundle* CAssetBundleManager::m_pAssetBundle;

CAssetBundleManager::CAssetBundleManager() {
	//LoadAssetBundle();
	CUtils::logger("[Manager]: Asset Bundle Loaded");
}

CAssetBundleManager::~CAssetBundleManager() {
	//m_pAssetBundle->Unload(true);
	CUtils::logger("[Manager]: Asset Bundle Unloaded");

	//for (auto& m_Material : m_mMaterials) {
	//	delete m_Material.second;
	//}
	//m_mMaterials.clear();
	CUtils::logger("[Manager]: Materials Cache Cleared");

	//for (auto& m_Shader : m_mShaders) {
	//	delete m_Shader.second;
	//}
	//m_mShaders.clear();
	CUtils::logger("[Manager]: Shaders Cache Cleared");
}

CShader* CAssetBundleManager::GetShader(EShaderType type) {
	auto it = m_mShaders.find(type);
	return it != m_mShaders.end() ? it->second : nullptr;
}

CMaterial* CAssetBundleManager::GetMaterial(EMaterialType type) {
	auto it = m_mMaterials.find(type);
	return it != m_mMaterials.end() ? it->second : nullptr;
}

void CAssetBundleManager::LoadAssetBundle() {
	/*auto bundle_data = (array<struct byte*>*)memory::Il2Cpp::il2cpp_array_new(API::GetClass("mscorlib.dll", "System", "Byte"), asset_bundle_data.size());
	std::memcpy(bundle_data->m_Items, asset_bundle_data.data(), asset_bundle_data.size());

	m_pAssetBundle = CAssetBundle::LoadFromMemory(bundle_data);
	if (m_pAssetBundle)
		CUtils::logger("Asset Bundle [SUCCESS]->%p", m_pAssetBundle);
	else
		CUtils::logger("Asset Bundle [FAILED]");*/
}

void CAssetBundleManager::LoadShaders() {
	//std::unordered_map<EShaderType, std::string> m_mShaderNames = {
	//	{ EShaderType::WIREFRAME, "Wireframe" },
	//	// other shaders
	//};

	//for (const auto& m_Shader : m_mShaderNames) {
	//	CShader* m_pLoadedShader = m_pAssetBundle->LoadAsset<CShader>(m_Shader.second.c_str());
	//	if (m_pLoadedShader) {
	//		m_mShaders[m_Shader.first] = m_pLoadedShader;
	//		CUtils::logger("Shader -> %s [SUCCESS]->%p", m_Shader.second.c_str(), m_pLoadedShader);
	//	} else {
	//		CUtils::logger("Shader -> %s [FAILED]", m_Shader.second.c_str());
	//	}
	//}
}

void CAssetBundleManager::LoadMaterials() {
	/*for (const auto& m_ShaderPair : m_mShaders) {
		EMaterialType m_eMaterialType = static_cast<EMaterialType>(m_ShaderPair.first);

		CMaterial* m_pMaterial = reinterpret_cast<CMaterial*>(memory::Il2Cpp::il2cpp_object_new(CMaterial::Pointer()));
		m_pMaterial = new CMaterial(m_ShaderPair.second);

		if (m_pMaterial) {
			m_mMaterials[m_eMaterialType] = m_pMaterial;
			CUtils::logger("Material -> %d [SUCCESS]->%p", m_eMaterialType, m_pMaterial);
		} else {
			CUtils::logger("Material -> %d [FAILED]", m_eMaterialType);
		}
	}*/
}
