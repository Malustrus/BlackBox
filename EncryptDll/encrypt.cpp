#include "pch.h"
#include <string>
#include <iostream> 
#include <fstream>
#include "7zpp.h"

using namespace std;


/// <summary>
/// Récupération de la date et heure ou juste de la date
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
string getCurrentDateTime(string s) {
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    localtime_s(&tstruct, &now);
    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
};

/// <summary>
/// Logger
/// </summary>
/// <param name="logMsg"></param>
void Logger(string logMsg) {

    string filePath = "log_" + getCurrentDateTime("date") + ".txt";
    string now = getCurrentDateTime("now");
    ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
    ofs << now << '\t' << logMsg << '\n';
    ofs.close();
}

/// <summary>
/// Retourne le nom de le l'executable appelante
/// </summary>
/// <returns></returns>
string getExecutableCallerName()
{   
    SevenZip::SevenZipLibrary lib;
    lib.Load();
    Logger("==> getExecutableCallerName()");
    TCHAR szExeFileName[MAX_PATH];

    GetModuleFileName(NULL, szExeFileName, MAX_PATH);   
    string fullName = szExeFileName;
    string name = fullName.substr(fullName.find_last_of("/\\") + 1);

    Logger("Executable caller full name = " + fullName);
    Logger("Executable caller name = " + name);

    Logger("<== getExecutableCallerName()");
    return fullName;
}

void EncryptFiles() 
{

}

BYTE* DecryptFiles() 
{
    return NULL;
}

/// <summary>
/// Peut être appelé depuis un exe C#
/// </summary>
extern "C" __declspec(dllexport) void test()
{
    getExecutableCallerName();
}


