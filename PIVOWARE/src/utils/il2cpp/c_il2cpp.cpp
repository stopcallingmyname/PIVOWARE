#include "includes.h"

std::map<std::string, Il2CppImage*> CIl2Cpp::m_pImagesMap = std::map<std::string, Il2CppImage*>();

bool CIl2Cpp::Initialize() {
	Il2CppDomain* m_pDomain = memory::Il2Cpp::il2cpp_domain_get();

	if (!m_pDomain)
		return false;

	Il2CppThread* m_pThread = memory::Il2Cpp::il2cpp_thread_attach(m_pDomain);

	if (!m_pThread)
		return false;

	size_t m_sAssembliesSize;
	Il2CppAssembly** m_pAssemblies = const_cast<Il2CppAssembly**>(memory::Il2Cpp::il2cpp_domain_get_assemblies(m_pDomain, &m_sAssembliesSize));


	for (size_t m_sIndex = 0; m_sIndex < m_sAssembliesSize; m_sIndex++) {
		Il2CppAssembly* m_pAssembly = m_pAssemblies[m_sIndex];

		if (!m_pAssembly)
			continue;

		Il2CppImage* m_pAssemblyImage = const_cast<Il2CppImage*>(memory::Il2Cpp::il2cpp_assembly_get_image(m_pAssembly));
		const char* m_cImageName = memory::Il2Cpp::il2cpp_image_get_name(m_pAssemblyImage);

		m_pImagesMap[m_cImageName] = m_pAssemblyImage;
	}

	memory::Il2Cpp::il2cpp_thread_detach(m_pThread);

	return true;
}

void CIl2Cpp::Uninitialize() {
	m_pImagesMap.clear();
}


Il2CppImage* CIl2Cpp::GetImage(std::string name) {
	return m_pImagesMap[name.c_str()];
}

Il2CppClass* CIl2Cpp::GetClass(std::string image_name, std::string _namespace, std::string name) {
	return memory::Il2Cpp::il2cpp_class_from_name(GetImage(image_name), _namespace.c_str(), name.c_str());
}

uintptr_t* CIl2Cpp::GetMethod(std::string image_name, std::string _namespace, std::string _class, std::string method_name, int params_count, std::vector<std::string> param_types) {

	Il2CppClass* m_pClass = GetClass(image_name, _namespace, _class);
	if (!m_pClass)
		return nullptr;

	for (int i = 0; i < m_pClass->method_count; ++i) {
		const MethodInfo* m_pMethodInfo = m_pClass->methods[i];

		//#ifdef _DEBUG
		//		CUtils::logger("Class: %s, Method: %s", m_pClass->name, m_pMethodInfo->name);
		//#endif 

		if (!m_pMethodInfo || m_pMethodInfo->name != method_name)
			continue;

		if (params_count != -1 && m_pMethodInfo->parameters_count != params_count)
			continue;

		if (!param_types.empty()) {
			if (m_pMethodInfo->parameters_count != param_types.size())
				continue;

			bool m_bMatch = true;

			for (int j = 0; j < m_pMethodInfo->parameters_count; ++j) {
				const Il2CppType* m_pParamType = m_pMethodInfo->parameters[j];
				const char* m_pParamTypeName = CUtils::ws2s(memory::Il2Cpp::il2cpp_type_get_name(m_pParamType)->chars).c_str();

				if (param_types[j] != m_pParamTypeName) {
					m_bMatch = false;
					break;
				}
			}

			if (!m_bMatch)
				continue;
		}

		return reinterpret_cast<uintptr_t*>(m_pMethodInfo->methodPointer);
	}

#ifdef _DEBUG
	CUtils::logger("Failed to find method: %s", method_name.c_str());
#endif 

	return nullptr;
}

//uintptr_t* CIl2Cpp::GetMethod(uintptr_t* _inst, std::string method_name, int params_count, std::vector<std::string> param_types) {
//	Il2CppClass* m_pClass = *reinterpret_cast<Il2CppClass**>(_inst);
//	if (!m_pClass) {
//		return nullptr;
//	}
//
//	for (int i = 0; i < m_pClass->method_count; ++i) {
//		const MethodInfo* m_pMethodInfo = m_pClass->methods[i];
//
//#ifdef _DEBUG
//		CUtils::logger("Class: %s, Method: %s", m_pClass->name, m_pMethodInfo->name);
//#endif 
//
//		if (!m_pMethodInfo || m_pMethodInfo->name != method_name)
//			continue;
//
//		if (params_count != -1 && m_pMethodInfo->parameters_count != params_count)
//			continue;
//
//		if (!param_types.empty()) {
//			if (m_pMethodInfo->parameters_count != param_types.size())
//				continue;
//
//			bool m_bMatch = true;
//
//			for (int j = 0; j < m_pMethodInfo->parameters_count; ++j) {
//				const Il2CppType* m_pParamType = m_pMethodInfo->parameters[j];
//				const char* m_pParamTypeName = CUtils::ws2s(memory::Il2Cpp::il2cpp_type_get_name(m_pParamType)->chars).c_str();
//
//				if (param_types[j] != m_pParamTypeName) {
//					m_bMatch = false;
//					break;
//				}
//			}
//
//			if (!m_bMatch)
//				continue;
//		}
//
//		return reinterpret_cast<uintptr_t*>(m_pMethodInfo->methodPointer);
//	}
//
//#ifdef _DEBUG
//	CUtils::logger("Failed to find method: %s", method_name.c_str());
//#endif 
//
//	return nullptr;
//}

uintptr_t* CIl2Cpp::GetMethod(uintptr_t* _inst, std::string method_name, int params_count, std::vector<std::string> param_types) {
	Il2CppClass* m_pClass = reinterpret_cast<Il2CppClass*>(_inst);
	if (!m_pClass) {
		return nullptr;
	}
	CUtils::logger("Class: %s", m_pClass->name);
	const MethodInfo* m_pMethodInfo = memory::Il2Cpp::il2cpp_class_get_method_from_name(m_pClass, method_name.c_str(), params_count);
	if (!m_pMethodInfo) {

#ifdef _DEBUG
		CUtils::logger("Failed to find method: %s", method_name.c_str());
#endif 

		return nullptr;
	}

#ifdef _DEBUG
	CUtils::logger("Class: %s, Method: %s", m_pClass->name, m_pMethodInfo->name);
#endif 

	if (!param_types.empty()) {
		if (m_pMethodInfo->parameters_count != param_types.size()) {
			return nullptr;
		}

		for (int j = 0; j < m_pMethodInfo->parameters_count; ++j) {
			const Il2CppType* m_pParamType = m_pMethodInfo->parameters[j];
			const char* m_pParamTypeName = CUtils::ws2s(memory::Il2Cpp::il2cpp_type_get_name(m_pParamType)->chars).c_str();

			if (param_types[j] != m_pParamTypeName) {
				return nullptr;
			}
		}
	}

	return reinterpret_cast<uintptr_t*>(m_pMethodInfo->methodPointer);
}


uintptr_t* CIl2Cpp::GetField(uintptr_t* _inst, std::string field_name) {
	Il2CppClass* m_pClass = *reinterpret_cast<Il2CppClass**>(_inst);
	if (!m_pClass) {
		return nullptr;
	}

	FieldInfo* m_pField = memory::Il2Cpp::il2cpp_class_get_field_from_name(m_pClass, field_name.c_str());
	if (!m_pField) {

#ifdef _DEBUG
		CUtils::logger("Failed to find field: %s", field_name.c_str());
#endif 

		return nullptr;
	}

#ifdef _DEBUG
	CUtils::logger("Class: %s, Field: %s", m_pClass->name, m_pField->name);
#endif

	uintptr_t* m_pFieldAddress = reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(_inst) + m_pField->offset);

	return m_pFieldAddress;
}

Il2CppReflectionType* CIl2Cpp::GetSystemType(Il2CppClass* _class) {
	const Il2CppType m_Type = *reinterpret_cast<Il2CppType*>(reinterpret_cast<uintptr_t>(_class) + 0x20);
	return reinterpret_cast<Il2CppReflectionType*>(memory::Il2Cpp::il2cpp_type_get_object(&m_Type));
}