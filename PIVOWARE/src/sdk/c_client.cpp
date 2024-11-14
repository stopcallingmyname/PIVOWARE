#include "includes.h"

bool& CClient::Active() {
	return *reinterpret_cast<bool*>(API::GetField(reinterpret_cast<uintptr_t*>(this), xorstr_("active")));
}

int& CClient::MyIndex() {
	return *reinterpret_cast<int*>(API::GetField(reinterpret_cast<uintptr_t*>(this), xorstr_("myindex")));
}
