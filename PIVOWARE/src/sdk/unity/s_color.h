#pragma once

struct SColor {
	static auto* Pointer() {
		return API::GetClass(xorstr_("UnityEngine.CoreModule.dll"), xorstr_("UnityEngine"), xorstr_("Color"));
	}

	SColor(std::vector<float>& color);
	SColor(float r, float g, float b, float a);

	float red;
	float green;
	float blue;
	float alpha;
};