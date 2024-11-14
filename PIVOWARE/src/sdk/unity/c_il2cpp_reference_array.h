#pragma once

template<typename T>
class CIl2CppReferenceArray {
public:
    int& Count();
    T& Item();

    auto& operator[](int index) {
        return Item()[index];
    }
};

template<typename T>
int& CIl2CppReferenceArray<T>::Count() {
    return *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18);
}

template<typename T>
T& CIl2CppReferenceArray<T>::Item() {
    return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + 0x20);
}
