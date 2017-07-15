#include "SDK.h"

void ConVar::SetValue(const char* value)
{
	typedef void(__thiscall* OriginalFn)(void*, const char*);
	return  GetVFunc<OriginalFn>(this, 14)(this, value);
}

void ConVar::SetValue(float value)
{
	typedef void(__thiscall* OriginalFn)(void*, float);
	return GetVFunc<OriginalFn>(this, 15)(this, value);
}

void ConVar::SetValue(int value)
{
	typedef void(__thiscall* OriginalFn)(void*, int);
	return GetVFunc<OriginalFn>(this, 16)(this, value);
}

void ConVar::SetValue(Color value)
{
	typedef void(__thiscall* OriginalFn)(void*, Color);
	return GetVFunc<OriginalFn>(this, 17)(this, value);
}

char* ConVar:: GetName()
{
	typedef char*(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 5)(this);
}

char* ConVar:: GetDefault()
{
	return pszDefaultValue;
}


MinspecCvar::MinspecCvar(const char* szCVar, const char* newname, float newvalue) : m_pConVar(nullptr)
{
	m_pConVar = Cvar->FindVar(szCVar);
	m_newvalue = newvalue;
	m_szReplacementName = newname;
	Spoof();
}

MinspecCvar::~MinspecCvar()
{
	if (ValidCvar())
	{
		Cvar->UnregisterConCommand(m_pConVar);
		m_pConVar->pszName = m_szOriginalName;
		m_pConVar->SetValue(m_OriginalValue);
		Cvar->RegisterConCommand(m_pConVar);
	}
}

bool MinspecCvar::ValidCvar()
{
	return m_pConVar != nullptr;
}
void MinspecCvar::Spoof()
{
	if (ValidCvar())
	{
		Cvar->UnregisterConCommand(m_pConVar);
		m_szOriginalName = m_pConVar->pszName;
		m_OriginalValue = m_pConVar->GetFloat();

		m_pConVar->pszName = m_szReplacementName;
		Cvar->RegisterConCommand(m_pConVar);
		m_pConVar->SetValue(m_newvalue);
	}
}

int MinspecCvar::GetInt()
{
	if (ValidCvar()) {
		return m_pConVar->GetInt();
	}
	return 0;
}

float MinspecCvar::GetFloat()
{
	if (ValidCvar()) {
		return m_pConVar->GetFloat();
	}
	return 0.0f;
}