#include "SDK.h"

void IInputSystem::EnableInput(bool bEnable)
{
	typedef void(__thiscall* OriginalFn)(void*, bool);
	return GetVFunc<OriginalFn>(this, 11)(this, bEnable);
}

void IInputSystem::ResetInputState()
{
	typedef void(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 39)(this);
}

bool IInputSystem::IsButtonDown(ButtonCode_t code)
{
	typedef bool(__thiscall* OriginalFn)(void*, ButtonCode_t);
	return GetVFunc<OriginalFn>(this, 15)(this, code);
}

void IInputSystem::GetCursorPosition(int* m_pX, int* m_pY)
{
	typedef void(__thiscall* OriginalFn)(void*, int*, int*);
	return GetVFunc<OriginalFn>(this, 56)(this, m_pX, m_pY);
}

const char* IInputSystem::ButtonCodeToString(ButtonCode_t code)
{
	typedef const char*(__thiscall* OriginalFn)(void*, ButtonCode_t);
	return GetVFunc<OriginalFn>(this, 40)(this, code);
}


ButtonCode_t IInputSystem::VirtualKeyToButtonCode(int nVirtualKey)
{
	typedef ButtonCode_t(*oVirtualKeyToButtonCode)(void*, int);
	return GetVFunc<oVirtualKeyToButtonCode>(this, 44)(this, nVirtualKey);
}
int IInputSystem::ButtonCodeToVirtualKey(ButtonCode_t code)
{
	typedef int(__thiscall* OriginalFn)(void*, ButtonCode_t);
	return GetVFunc<OriginalFn>(this, 45)(this, code);
}