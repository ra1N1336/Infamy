#pragma once

class IBaseClientDll
{
public:
	int GetScreenWidth(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return GetVFunc<OriginalFn>(this, 63)(this);
	}

	int GetScreenHeight(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return GetVFunc<OriginalFn>(this, 64)(this);
	}

	ClientClass* GetAllClasses();
};