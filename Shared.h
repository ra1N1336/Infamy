#pragma once
/*
<summary>
This is the common include file
</summary>
*/
#pragma warning(disable : 4244)
#pragma warning(disable : 4227)
#pragma warning(disable : 4172)
#pragma warning(disable : 4307)
#pragma warning(disable : 4996)
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <IOSTREAM>
#include <string>
#include <Psapi.h>
#include <lmcons.h>
#include <algorithm>
#include <vector>
#include <shlobj.h>
#include <time.h>
#include <random>
#include <sstream>
#include <fstream>
#include <shlwapi.h>
#include <iomanip>
#include <ctime>
#include <array>
#include <intrin.h>       
#include <iphlpapi.h>     
#include <process.h>
#include <Memory>
/*Debug Libs*/
#pragma comment(lib,"ntdll.lib")//binding issues
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")
extern void Request(int Method, LPCSTR Host, LPCSTR url, LPCSTR header, const char* data);
#define POST 1
#define GET 0
