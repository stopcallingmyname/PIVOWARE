class CSky : public CComponent {
public:
	static auto* Pointer() { return API::GetClass(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("Sky")); }
	static auto*& Instance() { return *reinterpret_cast<CSky**>(reinterpret_cast<char*>(Pointer()->static_fields)); }

	void SetSky(int mode, bool prazd = false);
};