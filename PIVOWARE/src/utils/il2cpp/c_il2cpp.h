
class CIl2Cpp {
public:
    static bool				                    Initialize();
    static void                                 Uninitialize();

    static Il2CppImage*                         GetImage(std::string name);
    static Il2CppClass*                         GetClass(std::string image_name, std::string _namespace, std::string name);
    static uintptr_t*                           GetMethod(std::string image_name, std::string _namespace, std::string _class, std::string method_name, int params_count = -1, std::vector<std::string> param_types = {});
    static uintptr_t*                           GetMethod(uintptr_t* _inst, std::string method_name, int params_count = -1, std::vector<std::string> param_types = {});
    static uintptr_t*                           GetField(uintptr_t* _inst, std::string field_name);
    static Il2CppReflectionType*                GetSystemType(Il2CppClass* _class);

private:
    static std::map<std::string, Il2CppImage*>  m_pImagesMap;
};

using API = CIl2Cpp;