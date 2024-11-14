class CClient {
public: 
	static auto* Pointer() { return API::GetClass(xorstr_("Assembly-CSharp.dll"), xorstr_(""), xorstr_("Client")); }
	static auto*& Instance() { return *reinterpret_cast<CClient**>(reinterpret_cast<char*>(Pointer()->static_fields)); }

	bool& Active();
	int& MyIndex();
};