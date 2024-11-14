#include "includes.h"

CConfigItem::CConfigItem(std::string name, void* pointer, std::string type) {
	this->m_sName = name;
	this->m_pPointer = pointer;
	this->m_sType = type;
}
