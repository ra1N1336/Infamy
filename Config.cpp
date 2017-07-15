#include "Config.h"
#include "json.hpp"
#include <WinInet.h>
#include "hwid.h"
#include <string>
#include <tchar.h>
#include "md5.h"
#include <algorithm>

Config* ConSys = new Config();
using json = nlohmann::json;

std::string configrecieved;
json Save;

using namespace std;

inline bool Check(std::string File)
{
	struct stat buf;
	return (stat(File.c_str(), &buf) == 0);
}

char Pic1[255], Sound[255];

inline const char* getMachineName()
{
	static char computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return &(computerName[0]);
}

inline DWORD getVolumeHash()
{
	DWORD serialNum = 0;
	GetVolumeInformation("c:\\", nullptr, 0, &serialNum, nullptr, nullptr, nullptr, 0);
	return serialNum;
}

bool Config::CheckConfigs()
{
	/*=====================================*/
	strcat(Path, XorStr("C:\\Infamy"));
	HANDLE File1, File2, File3, File4;
	CreateDirectoryA(Path, nullptr);
	strcpy(Path2, Path);
	strcpy(Path3, Path);
	strcpy(Path4, Path);
	strcpy(Picture, Path);
	strcpy(Picture2, Path);
	strcpy(Sound, Path);
	strcat(Picture, XorStr("\\Files"));
	CreateDirectoryA(Picture, nullptr);
	strcpy(Pic1, Picture);
	strcpy(Picture2, Picture);

	// Download from website
	strcat(Picture2, XorStr("\\beep.wav"));
	strcat(Picture, XorStr("\\hitsound.wav"));
	URLDownloadToFile(nullptr, XorStr("bigdownload beep.wav"), Picture2, 0, nullptr); Sleep(400);
	URLDownloadToFile(nullptr, XorStr("bigdownload hitsound.wav"), Picture, 0, nullptr); Sleep(400);


	// Delete the ini configs. xd
	strcat(Path, XorStr("\\Rage.ini"));
	strcat(Path2, XorStr("\\Legit.ini"));
	strcat(Path3, XorStr("\\Default.ini"));
	strcat(Path4, XorStr("\\League.ini"));
	/*=====================================*/
	DeleteFileA(Path);
	DeleteFileA(Path2);
	DeleteFileA(Path3);
	DeleteFileA(Path4);

	return true;
}

void find_and_replace(std::string& source, std::string const& find, std::string const& replace)
{
	for (std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}


bool PostURL(std::string url, std::string resource, std::string &data)
{
	return true;
}

bool GetConfig()
{
	return true;
}

void Config::SaveConfig()
{

}

void Config::LoadConfig()
{

}