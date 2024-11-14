#include "includes.h"

CDrawWorld::CDrawWorld() {}

void CDrawWorld::Overlay() {}

void CDrawWorld::Update() {
	if (g_Cvars.visuals.world.enable) {
		SkyboxChanger();
		Fog();
	}
}

void CDrawWorld::SkyboxChanger() {
	if (g_Cvars.visuals.world.skybox > 0) {
		if (!CSky::Instance())
			return;

		switch (g_Cvars.visuals.world.skybox)
		{
		case 1:
			CSky::Instance()->SetSky(0);
			break;
		case 2:
			CSky::Instance()->SetSky(1, true);
			break;
		case 3:
		{
			//if (g_pAssetBundleManager.get()) {
			//	
			//	CMaterial* m_pWireframeMaterial = g_pAssetBundleManager->GetMaterial(EMaterialType::WIREFRAME);
			//	//CMaterial* m_pWireframeMaterial = new CMaterial(CShader::Find("GUI/Text Shader"));
			//	if (m_pWireframeMaterial) {
			//		CRenderSettings::Skybox(m_pWireframeMaterial);
			//		//m_pWireframeMaterial->SetColor(xorstr_("_WireColor"), new SColor(g_Cvars.visuals.world.wireframe_color));
			//	}
			//}
			
			//CMaterial* m_pWireframeMaterial = new CMaterial(CShader::Find("GUI/Text Shader"));
			//if (m_pWireframeMaterial) {
			//	CRenderSettings::Skybox(m_pWireframeMaterial);
			//	//m_pWireframeMaterial->SetColor(xorstr_("_WireColor"), new SColor(g_Cvars.visuals.world.wireframe_color));
			//}
			break;
		}
		default:
			break;
		}
	}
}

void CDrawWorld::Fog() {
	CRenderSettings::Fog(g_Cvars.visuals.world.fog);
}

//void GetAllShaders() {
//	//CAssetBundleCreateRequest* m_pAssetBundleCreateRequest = CAssetBundle::LoadFromMemoryAsync(asset_bundle_data);
//	//if (!m_pAssetBundleCreateRequest)
//	//	CUtils::logger("LoadFromMemoryAsync [FAILED]");
//	//else
//	//	CUtils::logger("LoadFromMemoryAsync [SUCCESS]->%p", m_pAssetBundleCreateRequest);
//
//	//CAssetBundle* m_pAssetBundle = m_pAssetBundleCreateRequest->AssetBundle();
//	auto bundle_data = (array<struct byte*>*)memory::Il2Cpp::il2cpp_array_new(API::GetClass("mscorlib.dll", "System", "Byte"), asset_bundle_data.size());
//	std::memcpy(bundle_data->m_Items, asset_bundle_data.data(), asset_bundle_data.size());
//	CAssetBundle* m_pAssetBundle = CAssetBundle::LoadFromMemory(bundle_data);
//	if (!m_pAssetBundle)
//		CUtils::logger("AssetBundle [FAILED]");
//	else
//		CUtils::logger("AssetBundle [SUCCESS]->%p", m_pAssetBundle);
//
//	CShader* m_pWireframeShader = m_pAssetBundle->LoadAsset<CShader>("Wireframe");
//	if (!m_pWireframeShader)
//		CUtils::logger("LoadAsset [FAILED]");
//	else
//		CUtils::logger("LoadAsset [SUCCESS]->%p", m_pWireframeShader);
//
//	m_pWireframeMaterial = new CMaterial(m_pWireframeShader);
//	if (!m_pWireframeMaterial)
//		CUtils::logger("CreateWithShader [FAILED]");
//	else
//		CUtils::logger("CreateWithShader [SUCCESS]->%p", m_pWireframeMaterial);
//}