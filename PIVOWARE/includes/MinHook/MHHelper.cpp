#include "includes.h"

CHookData::CHookData() :
	m_bIsHooked(false),
	m_pOriginalAddress(nullptr),
	m_pNewAddress(nullptr),
	m_pOriginalFunction(nullptr),
	m_pProtectData()
{
	
}

bool CHookData::CreateHook(void* address, void* function) {
	if (m_bIsHooked)
	{
		if (address == m_pOriginalAddress && m_pNewAddress != function)
		{
			m_pNewAddress = function;
			EnableHook();
			return true;
		}

		DisableHook();
	}

	m_pOriginalAddress = address;
	m_pNewAddress = function;

	return true;
}

bool CHookData::EnableHook() {
	if (m_bIsHooked || !m_pOriginalAddress)
		return false;

	if (MH_CreateHook(m_pOriginalAddress, m_pNewAddress, &m_pOriginalFunction) == MH_OK && MH_EnableHook(m_pOriginalAddress) == MH_OK) {
		m_bIsHooked = true;
		return true;
	}

	m_bIsHooked = false;
	return false;
}

void CHookData::DisableHook() {
	if (!m_bIsHooked || !m_pOriginalAddress)
		return;

	MH_DisableHook(m_pOriginalAddress);
	MH_RemoveHook(m_pOriginalAddress);

	m_bIsHooked = false;
}