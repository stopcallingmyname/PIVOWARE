#pragma once 

class CRenderer : public CComponent { 
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Renderer")); }

	void Enabled(bool value);
	bool Enabled();

	CMaterial* Material();
	void Material(CMaterial* material);
};