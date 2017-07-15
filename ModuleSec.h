#pragma once
#include "Shared.h"
/* Kidua gave me this forever ago, prob from some online lib*/
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_MODULE_DUMMY_
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;

	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct _PEB_LDR_DATA_DUMMY_
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct PEB_DUMMY_
{
	PVOID Dummy1;
	PVOID Dummy2;
	PVOID Dummy3;
	PPEB_LDR_DATA LDR_Data;
} PEB_DUMMY, *PPEB_DUMMY;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	PVOID ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StdInputHandle;
	HANDLE StdOutputHandle;
	HANDLE StdErrorHandle;
	UNICODE_STRING CurrentDirectoryPath;
	HANDLE CurrentDirectoryHandle;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PVOID Environment;
	ULONG StartingPositionLeft;
	ULONG StartingPositionTop;
	ULONG Width;
	ULONG Height;
	ULONG CharWidth;
	ULONG CharHeight;
	ULONG ConsoleTextAttributes;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopName;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef void (*PPEBLOCKROUTINE)(PVOID PebLock);

typedef struct _PEB_FREE_BLOCK
{
	_PEB_FREE_BLOCK* Next;
	DWORD Size;
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _PEB
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	BOOLEAN Spare;
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA LoaderData;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PVOID FastPebLock;
	PPEBLOCKROUTINE FastPebLockRoutine;
	PPEBLOCKROUTINE FastPebUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID* KernelCallbackTable;
	PVOID EventLogSection;
	PVOID EventLog;
	PPEB_FREE_BLOCK FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[0x2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID ReadOnlySharedMemoryHeap;
	PVOID* ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;
	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;
	BYTE Spare2[0x4];
	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;
	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID** ProcessHeaps;
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	PVOID GdiDCAttributeList;
	PVOID LoaderLock;
	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	ULONG OSBuildNumber;
	ULONG OSPlatformId;
	ULONG ImageSubSystem;
	ULONG ImageSubSystemMajorVersion;
	ULONG ImageSubSystemMinorVersion;
	ULONG GdiHandleBuffer[0x22];
	ULONG PostProcessInitRoutine;
	ULONG TlsExpansionBitmap;
	BYTE TlsExpansionBitmapBits[0x80];
	ULONG SessionId;
} PEB, *PPEB;

typedef struct _TEB
{
	NT_TIB Tib;
	PVOID EnvironmentPointer;
	CLIENT_ID Cid;
	PVOID ActiveRpcInfo;
	PVOID ThreadLocalStoragePointer;
	PPEB Peb;
	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PVOID CsrClientThread;
	PVOID Win32ThreadInfo;
	ULONG Win32ClientInfo[0x1F];
	PVOID WOW32Reserved;
	ULONG CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PVOID SystemReserved1[0x36];
	PVOID Spare1;
	ULONG ExceptionCode;
	ULONG SpareBytes1[0x28];
	PVOID SystemReserved2[0xA];
	ULONG GdiRgn;
	ULONG GdiPen;
	ULONG GdiBrush;
	CLIENT_ID RealClientId;
	PVOID GdiCachedProcessHandle;
	ULONG GdiClientPID;
	ULONG GdiClientTID;
	PVOID GdiThreadLocaleInfo;
	PVOID UserReserved[5];
	PVOID GlDispatchTable[0x118];
	ULONG GlReserved1[0x1A];
	PVOID GlReserved2;
	PVOID GlSectionInfo;
	PVOID GlSection;
	PVOID GlTable;
	PVOID GlCurrentRC;
	PVOID GlContext;
	NTSTATUS LastStatusValue;
	UNICODE_STRING StaticUnicodeString;
	WCHAR StaticUnicodeBuffer[0x105];
	PVOID DeallocationStack;
	PVOID TlsSlots[0x40];
	LIST_ENTRY TlsLinks;
	PVOID Vdm;
	PVOID ReservedForNtRpc;
	PVOID DbgSsReserved[0x2];
	ULONG HardErrorDisabled;
	PVOID Instrumentation[0x10];
	PVOID WinSockData;
	ULONG GdiBatchCount;
	ULONG Spare2;
	ULONG Spare3;
	ULONG Spare4;
	PVOID ReservedForOle;
	ULONG WaitingOnLoaderLock;
	PVOID StackCommit;
	PVOID StackCommitMax;
	PVOID StackReserved;
} TEB, *PTEB;

inline PPEB_DUMMY __declspec(naked) GetPEB(void)
{
	_asm
		{
			mov eax, fs:[0x30];
			retn;
		}
}

inline void HideModuleFromPEB(HINSTANCE hInstance)
{
	auto PEB = GetPEB();

	auto FirstEntryInLoadOrder = static_cast<PLIST_ENTRY>(&PEB->LDR_Data->InLoadOrderModuleList);
	auto FirstEntryInMemoryOrder = static_cast<PLIST_ENTRY>(&PEB->LDR_Data->InMemoryOrderModuleList);
	auto FirstEntryInInitOrder = static_cast<PLIST_ENTRY>(&PEB->LDR_Data->InInitializationOrderModuleList);

	for (auto TempEntry = FirstEntryInLoadOrder->Flink; TempEntry != FirstEntryInLoadOrder; TempEntry = TempEntry->Flink)
	{
		auto TempModule = reinterpret_cast<PLDR_MODULE>(reinterpret_cast<DWORD>(TempEntry) - 0 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}

	for (auto TempEntry = FirstEntryInMemoryOrder->Flink; TempEntry != FirstEntryInMemoryOrder; TempEntry = TempEntry->Flink)
	{
		auto TempModule = reinterpret_cast<PLDR_MODULE>(reinterpret_cast<DWORD>(TempEntry) - 1 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}

	for (auto TempEntry = FirstEntryInInitOrder->Flink; TempEntry != FirstEntryInInitOrder; TempEntry = TempEntry->Flink)
	{
		auto TempModule = reinterpret_cast<PLDR_MODULE>(reinterpret_cast<DWORD>(TempEntry) - 2 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}
}

inline void RemovePeHeader(DWORD ModuleBase)
{
	auto pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(ModuleBase);
	auto pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(pDosHeader) + static_cast<DWORD>(pDosHeader->e_lfanew));

	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return;

	if (pNTHeader->FileHeader.SizeOfOptionalHeader)
	{
		DWORD Protect;
		auto Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
		VirtualProtect(reinterpret_cast<void*>(ModuleBase), Size, PAGE_EXECUTE_READWRITE, &Protect);
		RtlZeroMemory(reinterpret_cast<void*>(ModuleBase), Size);
		VirtualProtect(reinterpret_cast<void*>(ModuleBase), Size, Protect, &Protect);
	}
}

inline void HideModule(HANDLE hModule)
{
	auto pDOSHeader = static_cast<PIMAGE_DOS_HEADER>(hModule);
	if (pDOSHeader->e_magic == IMAGE_DOS_SIGNATURE)
	{
		auto pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(pDOSHeader) + static_cast<DWORD>(pDOSHeader->e_lfanew));
		if (pNTHeader->Signature == IMAGE_NT_SIGNATURE)
		{
			DWORD dwOld, dwSize = pNTHeader->OptionalHeader.SizeOfHeaders;
			if (VirtualProtect(static_cast<LPVOID>(pDOSHeader), dwSize, PAGE_READWRITE, &dwOld))
			{
				memset(static_cast<void*>(pDOSHeader), 0, dwSize);
				VirtualProtect(static_cast<LPVOID>(pDOSHeader), dwSize, dwOld, &dwOld);
			}
		}
		_TEB* pTeb = nullptr;
		_asm
			{
				mov eax, fs:[0x18]
				mov pTeb, eax
			}
		auto pList = &pTeb->Peb->LoaderData->InLoadOrderModuleList;
		for (auto pEntry = pList->Flink; pEntry != pList; pEntry = pEntry->Flink)
		{
			auto pModule = reinterpret_cast<PLDR_MODULE>(pEntry);
			if (pModule->BaseAddress == hModule)
			{
				pEntry = &pModule->InLoadOrderModuleList;
				pEntry->Blink->Flink = pEntry->Flink;
				pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->InMemoryOrderModuleList;
				pEntry->Blink->Flink = pEntry->Flink;
				pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->InInitializationOrderModuleList;
				pEntry->Blink->Flink = pEntry->Flink;
				pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->HashTableEntry;
				pEntry->Blink->Flink = pEntry->Flink;
				pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				memset(pModule->FullDllName.Buffer, 0, pModule->FullDllName.Length);
				memset(pModule, 0, sizeof(LDR_MODULE));
				break;
			}
		}
	}
}

inline bool DestroyModuleHeader(HMODULE hModule)
{
	auto dwStartOffset = reinterpret_cast<DWORD>(hModule);

	auto pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(dwStartOffset);
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return false;

	auto pNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(dwStartOffset + pDosHeader->e_lfanew);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return false;

	DWORD dwOldProtection = NULL;
	if (!VirtualProtect(static_cast<PVOID>(hModule), pNtHeader->OptionalHeader.SizeOfHeaders, PAGE_EXECUTE_READWRITE, &dwOldProtection))
		return false;

	ZeroMemory(static_cast<PVOID>(hModule), pNtHeader->OptionalHeader.SizeOfHeaders);
	VirtualProtect(static_cast<PVOID>(hModule), pNtHeader->OptionalHeader.SizeOfHeaders, dwOldProtection, &dwOldProtection);

	return true;
}

