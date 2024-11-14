#pragma once

class CObject {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Object")); }

	Il2CppString* Name();
};