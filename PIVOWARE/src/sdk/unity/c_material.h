#pragma once

class CMaterial : public CObject {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Material")); }

	CMaterial(CShader* shader);

	CShader* Shader();
	void Shader(CShader* shader);
	static CMaterial* CreateWithShader(CShader* shader);

	// Set color by property name
	void SetColor(const char* name, SColor* value);
	void Color(SColor* value);
};