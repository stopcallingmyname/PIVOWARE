
class CHookData {
public:
	CHookData();

	bool IsHooked() { return m_bIsHooked; }

	bool CreateHook(void* address, void* function);
	bool EnableHook();

	void DisableHook();
private:
	bool m_bIsHooked;

	void* m_pOriginalAddress;
	void* m_pNewAddress;

	unsigned char m_pProtectData[14];
public:
	void* m_pOriginalFunction;
};

#define MAKE_HOOK(ref, address, function)\
        ref = CHookData();\
        ref.CreateHook(reinterpret_cast<void*>(address), reinterpret_cast<void*>(function));\
        ref.EnableHook();

#define RESET_HOOK(ref) ref.DisableHook();