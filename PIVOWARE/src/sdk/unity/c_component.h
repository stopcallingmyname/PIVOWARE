#pragma once

class CComponent : public CObject {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Component")); }
};