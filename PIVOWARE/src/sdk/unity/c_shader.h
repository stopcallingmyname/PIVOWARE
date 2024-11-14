#pragma once

class CShader : public CObject {
public:
	static auto* Pointer() {
		return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Shader"));
	}

	static CShader* Find(const char* name);
};