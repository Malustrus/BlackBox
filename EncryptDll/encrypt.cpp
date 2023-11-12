#include "pch.h"
#include <cryptlib.h>
#include <shake.h>
#include <channels.h>
#include <filters.h>
#include <files.h>
#include <hex.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <bit7z/bitfilecompressor.hpp>

using namespace std;


/// <summary>
/// R�cup�ration de la date et heure ou juste de la date
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

string getHashesFile()
{
    std::string s1;
    CryptoPP::SHAKE256 hash;

    CryptoPP::HashFilter f1(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(s1)));

    CryptoPP::ChannelSwitch cs;
    cs.AddDefaultRoute(f1);

    //CryptoPP::FileSource(getExecutableCallerName().c_str(), true /*pumpAll*/, new CryptoPP::Redirector(cs));

    Logger("mot de passe : " + s1);

    return s1;
}

void EncryptFiles() 
{
    try
    {
        Logger("test1.1");
        bit7z::Bit7zLibrary lib{ "7z.dll" };
        Logger("test1.2");
        bit7z::BitFileCompressor compressor{ lib, bit7z::BitFormat::Zip };
        Logger("test1.3");
        std::vector< std::string > files = { "D:\\OneDrive\\Documents\\1_Projet\\Chiffrement\\test.txt" };
        Logger("test2");
        compressor.compress(files, "output_archive.zip");
        compressor.setPassword(getHashesFile(), true);
        compressor.compressFiles(files, "protected_archive.zip");
        compressor.setUpdateMode(bit7z::UpdateMode::Append);
        compressor.compressFiles(files, "existing_archive.zip");
        Logger("test4");
    }
    catch (const bit7z::BitException& ex)
    {
        Logger("erreur");
    }
}



BYTE* DecryptFiles() 
{
    return NULL;
}

/// <summary>
/// Peut �tre appel� depuis un exe C#
/// </summary>
extern "C" __declspec(dllexport) void test()
{
    EncryptFiles();
}

