#pragma once

class CRenderSettings {
public:
	static auto* Pointer() {
		return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("RenderSettings"));
	}

	static void Reset();
	static void Fog(bool value);
	static CMaterial* Skybox();
	static void Skybox(CMaterial* value);
};