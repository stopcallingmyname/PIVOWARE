#pragma once

class CCamera : public CComponent {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Camera")); }

	static CCamera* Main();

	float Aspect();
	void Aspect(float value);
};