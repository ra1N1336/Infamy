#pragma once

class IAppSystem
{
public:
	virtual ~IAppSystem()
	{
	}

	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
};

class ICVar : public IAppSystem
{
public:
	virtual void			func10() = 0;															 
	virtual void			RegisterConCommand( ConVar *pCommandBase ) = 0; 
	virtual void			UnregisterConCommand( ConVar *pCommandBase ) = 0;
	virtual void			func13() = 0;
	virtual ConVar			*FindVar( const char *var_name ) = 0;
	virtual void			func15() = 0;
	virtual void			func16() = 0;
	virtual void			func17() = 0;
	virtual void			func18() = 0;
	virtual void			func19() = 0;
	virtual void			func20() = 0;

	void const ConsoleColorPrintf(const Color& clr, const char *pFormat, ...)
	{
		typedef void(__cdecl *OriginalFn)(void*, const Color&, const char *, ...);

		if (pFormat == nullptr)
			return;

		char buf[8192];

		va_list list;
		va_start(list, pFormat);
		_vsnprintf(buf, sizeof(buf) - 1, pFormat, list);
		va_end(list);
		buf[sizeof(buf) - 1] = 0;

		GetVFunc<OriginalFn>(this, 25)(this, clr, buf, list);
	}
};