#pragma once


class CHudChat
{
public:
	void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...)
	{
		GetVFunc<void(__cdecl*)(void*, int, int, const char*, ...)>(this, 26)(this, iPlayerIndex, iFilter, fmt);
	}
};

class IClientModeShared
{
public:
	CHudChat *m_pChat;

}; 