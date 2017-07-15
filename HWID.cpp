#include "HWID.h"
#include <TlHelp32.h>
#include  "Options.h"
#include <WinInet.h>
#include <gdiplus.h>
cSecurity* g_pSecurity = new cSecurity;
cSecurity::cSecurity()
{
	buf1 = NULL;
	buf2 = NULL;
	User = "null";
}
DWORD GetProcessIdByName(LPCTSTR name)
{
	PROCESSENTRY32 pe32;
	HANDLE snapshot = nullptr;
	DWORD pid = 0;

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &pe32)) {
			do {
				std::string sName = pe32.szExeFile;
				std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);

				if (!lstrcmp(sName.c_str(), name)) {
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &pe32));
		}

		CloseHandle(snapshot);
	}

	return pid;
}


inline BOOL CanOpenCsrss()
{
	HANDLE hCsrss = nullptr;

	hCsrss = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessIdByName(XorStr("csrss.exe")));

	if (hCsrss != nullptr)
	{
		CloseHandle(hCsrss);
		return TRUE;
	}
	else
		return FALSE;

}
inline bool checkGlobalFlags()
{
	DWORD NtGlobalFlags;
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax + 68h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70)
		return true;

	return false;
}
inline uint16_t cSecurity::hashMacAddress(PIP_ADAPTER_INFO info)
{
	uint16_t hash = 0;
	for (auto i = 0; i < info->AddressLength; i++)
	{
		hash += (info->Address[i] << ((i & 1) * 8));
	}
	return hash;
}
inline void walkProcessList()
{
	std::vector<std::string> m_processList;
	m_processList.push_back(XorStr("ollydbg.exe"));
	m_processList.push_back(XorStr("wireshark.exe"));
	m_processList.push_back(XorStr("lordpe.exe"));
	m_processList.push_back(XorStr("hookshark.exe"));
	m_processList.push_back(XorStr("idag.exe"));
	m_processList.push_back(XorStr("MPGH Virus Scan Tool v6.exe"));

	for (unsigned int ax = 0; ax < m_processList.size(); ax++)
	{
		std::string sProcess = m_processList.at(ax);
		if (GetProcessIdByName(sProcess.c_str()) != 0)
		{
			Options.Cheat.Uninject = true;
		}
	}
}

inline void doChecks()
{
	if (GetProcessIdByName(XorStr("TeamViewer.exe")) != 0)
	{
		MessageBox(0, XorStr("Close Teamviewer"),XorStr("TeamViewer"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	HANDLE hModule = GetModuleHandle(XorStr("tv_w32.dll"));

	if (hModule != 0)
	{
		MessageBox(0, XorStr("Please close Teamviewer"), XorStr("TeamViewer"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	walkProcessList();

}
inline void cSecurity::getMacHash(uint16_t& mac1, uint16_t& mac2)
{
	IP_ADAPTER_INFO AdapterInfo[32];
	DWORD dwBufLen = sizeof(AdapterInfo);
	auto dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
	if (dwStatus != ERROR_SUCCESS)
		return;
	auto pAdapterInfo = AdapterInfo;
	mac1 = hashMacAddress(pAdapterInfo);
	if (pAdapterInfo->Next)
		mac2 = hashMacAddress(pAdapterInfo->Next);
	if (mac1 > mac2)
	{
		auto tmp = mac2;
		mac2 = mac1;
		mac1 = tmp;
	}
}

inline uint16_t cSecurity::getVolumeHash()
{
	DWORD serialNum = 0;
	GetVolumeInformation("c:\\", nullptr, 0, &serialNum, nullptr, nullptr, nullptr, 0);
	auto hash = static_cast<uint16_t>((serialNum + (serialNum >> 16)) & 0xFFFF);
	return hash;
}

inline uint16_t cSecurity::getCpuHash()
{
	int cpuinfo[4] = { 0, 0, 0, 0 };
	__cpuid(cpuinfo, 0);
	uint16_t hash = 0;
	auto ptr = reinterpret_cast<uint16_t*>(&cpuinfo[0]);
	for (auto i = 0; i < 8; i++)
		hash += ptr[i];
	return hash;
}

inline const char* cSecurity::getMachineName()
{
	static char computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return &(computerName[0]);
}
EXTERN_C NTSTATUS NTAPI RtlAdjustPrivlege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);
inline bool cSecurity::Authenticate()
{
	return true;
}

bool cSecurity::Trampoline(bool tram = false, int set = 7)
{
	if (!tram || set != 0)
		Trampoline(tram, set);
	else
		if (Detour(false, 6556156165615))
			return true;
	return false;
}

bool cSecurity::Detour(bool detour = true, int max = 0)
{
	if (!max)
		Detour();
	if (detour)
		Detour();

	if (!detour && max)
		if (BackroundWorker(false))
			return true;
}
static bool one = true;
bool cSecurity::BackroundWorker(bool Invalid = true)
{
	doChecks();
	return true;
	if (Invalid)
		return false;
	BackroundWorker();
}
std::string ReadFileIntoByteArray(PCHAR fileName)
{
	std::string sNoob;
	size_t iLen;
	std::ifstream fl(fileName, std::ios::binary);

	if (fl)
	{
		fl.seekg(0, std::ios::end);

		iLen = fl.tellg();

		sNoob.reserve(iLen);

		fl.seekg(0, std::ios::beg);

		sNoob.assign((std::istreambuf_iterator<char>(fl)),
			std::istreambuf_iterator<char>());

		fl.close();
	}


	return sNoob;
}
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0; // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1; // Failure
	}

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1; // Failure
	}

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; // Success
		}
	}

	free(pImageCodecInfo);
	return -1; // Failure
}
bool cSecurity::RunSecurityChecks()
{
	//doChecks();
	if (Authenticate())
		return true;//how it is rn, I patched it with two bytes ssoooooooooooooooooooooooooooooo fix it soon
	return false;
}

