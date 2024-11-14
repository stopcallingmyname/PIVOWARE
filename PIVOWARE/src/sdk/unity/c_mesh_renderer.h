#pragma once 

class CMeshRenderer : public CRenderer {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("MeshRenderer")); }
};