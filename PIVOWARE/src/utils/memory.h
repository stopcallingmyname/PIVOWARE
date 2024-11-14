#pragma once

namespace memory {

	inline  uintptr_t get_base_address() {
		return reinterpret_cast<uintptr_t>(GetModuleHandleA("GameAssembly.dll"));
	}


    inline HMODULE get_game_assembly_module() {
        return GetModuleHandleA("GameAssembly.dll");
    }

    inline LPVOID get_proc_address(const char* proc_name) {
        HMODULE m_hModule = get_game_assembly_module();
        if (!m_hModule) {
            return nullptr;
        }
        return GetProcAddress(m_hModule, proc_name);
    }

    namespace Il2Cpp {

        inline Il2CppMethodPointer il2cpp_resolve_icall(const char* method_name) {
            auto m_pMethod = reinterpret_cast<Il2CppMethodPointer(CDECL*)(const char*)>(get_proc_address("il2cpp_resolve_icall"));
            return m_pMethod ? m_pMethod(method_name) : nullptr;
        }

        inline const Il2CppImage* il2cpp_get_corlib() {
            auto m_pMethod = reinterpret_cast<const Il2CppImage * (*)()>(get_proc_address("il2cpp_get_corlib"));
            return m_pMethod ? m_pMethod() : nullptr;
        }

        inline void* il2cpp_alloc(size_t size) {
            auto m_pMethod = reinterpret_cast<void* (*)(size_t)>(get_proc_address("il2cpp_alloc"));
            return m_pMethod ? m_pMethod(size) : nullptr;
        }

        inline void il2cpp_free(void* ptr) {
            auto m_pMethod = reinterpret_cast<void(*)(void*)>(get_proc_address("il2cpp_free"));
            if (m_pMethod) {
                m_pMethod(ptr);
            }
        }

        inline const Il2CppImage* il2cpp_assembly_get_image(const Il2CppAssembly* assembly) {
            auto m_pMethod = reinterpret_cast<const Il2CppImage * (*)(const Il2CppAssembly*)>(get_proc_address("il2cpp_assembly_get_image"));
            return m_pMethod ? m_pMethod(assembly) : nullptr;
        }

        inline const char* il2cpp_image_get_name(const Il2CppImage* image) {
            auto m_pMethod = reinterpret_cast<const char* (*)(const Il2CppImage*)>(get_proc_address("il2cpp_image_get_name"));
            return m_pMethod ? m_pMethod(image) : nullptr;
        }

        inline Il2CppArray* il2cpp_array_new(Il2CppClass* elementTypeInfo, il2cpp_array_size_t length) {
            auto m_pMethod = reinterpret_cast<Il2CppArray * (*)(Il2CppClass*, il2cpp_array_size_t)>(get_proc_address("il2cpp_array_new"));
            return m_pMethod ? m_pMethod(elementTypeInfo, length) : nullptr;
        }

        inline Il2CppClass* il2cpp_class_from_name(const Il2CppImage* image, const char* namespaze, const char* name) {
            auto m_pMethod = reinterpret_cast<Il2CppClass * (*)(const Il2CppImage*, const char*, const char*)>(get_proc_address("il2cpp_class_from_name"));
            return m_pMethod ? m_pMethod(image, namespaze, name) : nullptr;
        }

        inline Il2CppClass* il2cpp_class_get_nested_types(Il2CppClass* klass, void** iter) {
            auto m_pMethod = reinterpret_cast<Il2CppClass * (*)(Il2CppClass*, void**)>(get_proc_address("il2cpp_class_get_nested_types"));
            return m_pMethod ? m_pMethod(klass, iter) : nullptr;
        }

        inline Il2CppType* il2cpp_class_get_type(Il2CppClass* klass) {
            auto m_pMethod = reinterpret_cast<Il2CppType * (*)(Il2CppClass*)>(get_proc_address("il2cpp_class_get_type"));
            return m_pMethod ? m_pMethod(klass) : nullptr;
        }

        inline Il2CppDomain* il2cpp_domain_get() {
            return reinterpret_cast<Il2CppDomain * (*)()>(get_proc_address("il2cpp_domain_get"))();
        }

        inline const Il2CppAssembly* il2cpp_domain_assembly_open(Il2CppDomain* domain, const char* name) {
            auto m_pMethod = reinterpret_cast<const Il2CppAssembly * (*)(Il2CppDomain*, const char*)>(get_proc_address("il2cpp_domain_assembly_open"));
            return m_pMethod ? m_pMethod(domain, name) : nullptr;
        }

        inline const Il2CppAssembly** il2cpp_domain_get_assemblies(const Il2CppDomain* domain, size_t* size) {
            auto m_pMethod = reinterpret_cast<const Il2CppAssembly * *(*)(const Il2CppDomain*, size_t*)>(get_proc_address("il2cpp_domain_get_assemblies"));
            return m_pMethod ? m_pMethod(domain, size) : nullptr;
        }

        inline Il2CppObject* il2cpp_object_new(const Il2CppClass* klass) {
            auto m_pMethod = reinterpret_cast<Il2CppObject * (*)(const Il2CppClass*)>(get_proc_address("il2cpp_object_new"));
            return m_pMethod ? m_pMethod(klass) : nullptr;
        }

        inline void* il2cpp_object_unbox(Il2CppObject* obj) {
            auto m_pMethod = reinterpret_cast<void* (*)(Il2CppObject*)>(get_proc_address("il2cpp_object_unbox"));
            return m_pMethod ? m_pMethod(obj) : nullptr;
        }

        inline Il2CppObject* il2cpp_value_box(Il2CppClass* klass, void* data) {
            auto m_pMethod = reinterpret_cast<Il2CppObject * (*)(Il2CppClass*, void*)>(get_proc_address("il2cpp_value_box"));
            return m_pMethod ? m_pMethod(klass, data) : nullptr;
        }

        inline void il2cpp_runtime_class_init(Il2CppClass* klass) {
            auto m_pMethod = reinterpret_cast<void(*)(Il2CppClass*)>(get_proc_address("il2cpp_runtime_class_init"));
            return  m_pMethod ? m_pMethod(klass) : (void)0;
        }

        inline Il2CppString* il2cpp_string_new(const char* str) {
            auto m_pMethod = reinterpret_cast<Il2CppString * (*)(const char*)>(get_proc_address("il2cpp_string_new"));
            return m_pMethod ? m_pMethod(str) : nullptr;
        }

        inline Il2CppString* il2cpp_string_new_utf16(const Il2CppChar* text, int32_t len) {
            auto m_pMethod = reinterpret_cast<Il2CppString * (*)(const Il2CppChar*, int32_t)>(get_proc_address("il2cpp_string_new_utf16"));
            return m_pMethod ? m_pMethod(text, len) : nullptr;
        }

        inline Il2CppThread* il2cpp_thread_attach(Il2CppDomain* domain) {
            auto m_pMethod = reinterpret_cast<Il2CppThread * (*)(Il2CppDomain*)>(get_proc_address("il2cpp_thread_attach"));
            return m_pMethod ? m_pMethod(domain) : nullptr;
        }

        inline void il2cpp_thread_detach(Il2CppThread* thread) {
            auto m_pMethod = reinterpret_cast<void(*)(Il2CppThread*)>(get_proc_address("il2cpp_thread_detach"));
            if (m_pMethod) {
                m_pMethod(thread);
            }
        }

        inline Il2CppThread* il2cpp_thread_current() {
            auto m_pMethod = reinterpret_cast<Il2CppThread * (*)()>(get_proc_address("il2cpp_thread_current"));
            if (!m_pMethod) {
                printf("Failed to get proc address for il2cpp_thread_detach");
                return nullptr;
            }
            return m_pMethod ? m_pMethod() : nullptr;
        }

        inline Il2CppObject* il2cpp_type_get_object(const Il2CppType* type) {
            auto m_pMethod = reinterpret_cast<Il2CppObject * (*)(const Il2CppType*)>(get_proc_address("il2cpp_type_get_object"));
            return m_pMethod ? m_pMethod(type) : nullptr;
        }

        inline Il2CppString* il2cpp_type_get_name(const Il2CppType* type) {
            auto m_pMethod = reinterpret_cast<Il2CppString * (*)(const Il2CppType*)>(get_proc_address("il2cpp_type_get_name"));
            return m_pMethod ? m_pMethod(type) : nullptr;
        }

        inline FieldInfo* il2cpp_class_get_field_from_name(Il2CppClass* klass, const char* name) {
            auto m_pMethod = reinterpret_cast<FieldInfo * (*)(Il2CppClass*, const char*)>(get_proc_address("il2cpp_class_get_field_from_name"));
            return m_pMethod ? m_pMethod(klass, name) : nullptr;
        }

        inline MethodInfo* il2cpp_class_get_method_from_name(Il2CppClass* klass, const char* name, int params_count) {
            auto m_pMethod = reinterpret_cast<MethodInfo * (*)(Il2CppClass*, const char*, int)>(get_proc_address("il2cpp_class_get_method_from_name"));
            return m_pMethod ? m_pMethod(klass, name, params_count) : nullptr;
        }

        inline Il2CppObject* il2cpp_runtime_invoke(const MethodInfo* method, void* obj, void** params, Il2CppException** exc) {
            auto m_pMethod = reinterpret_cast<Il2CppObject * (*)(const MethodInfo*, void*, void**, Il2CppException**)>(get_proc_address("il2cpp_runtime_invoke"));
            return m_pMethod ? m_pMethod(method, obj, params, exc) : nullptr;
        }
    }
}