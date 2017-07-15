#pragma once

class ConVar
{
public:
	void SetValue(const char *value);
	void SetValue(float value);
	void SetValue(int value);
	void SetValue(Color value);
	void InternalSetString(const char* str);
	char* GetName();
	char* GetDefault();

	float GetFloat(void) const
	{
		auto temp = *(int*)(&fValue);
		auto temp_result = (int)(temp ^ (DWORD)this);

		return *(float*)(&temp_result);
	}

	int GetInt(void) const
	{
		auto temp = *(int*)(&nValue);
		auto temp_result = (int)(temp ^ (DWORD)this);
		return *(int*)(&temp_result);
	}

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	const char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 
};//Size=0x0048


class MinspecCvar
{
public:
	MinspecCvar(const char* szCVar, const char* newname, float newvalue);
	~MinspecCvar();

	bool ValidCvar();
	void Spoof();

	template<typename T>
	void SetValue(T value);

	int	GetInt();
	float GetFloat();
	const char* GetString();
private:
	ConVar* m_pConVar;

	const char* m_szOriginalName;
	const char* m_szReplacementName;
	float m_OriginalValue;
	float m_newvalue;
};

template<typename T>
inline void MinspecCvar::SetValue(T value)
{
	m_pConVar->SetValue(value);
}