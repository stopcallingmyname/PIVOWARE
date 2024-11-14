#include "includes.h"

void CSky::SetSky(int mode, bool prazd) {
	using set_sky_t = void(__cdecl*)(CSky*, int, bool);
	static set_sky_t set_sky;

	if (!set_sky)
		set_sky = reinterpret_cast<set_sky_t>(API::GetMethod(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("Sky"), xorstr_("SetSky")));
	return set_sky ? set_sky(this, mode, prazd) : (void)0;
}
