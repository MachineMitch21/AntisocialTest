
#ifndef ANTISOCIAL_H
#define ANTISOCIAL_H

#ifdef __WIN32__
#include <windows.h>
#include <fstream>

//Defining entry point to DLL for windows
BOOL APIENTRY DLLMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);


#ifdef ANTISOCIAL_EXPORT
#define ANTISOCIAL_API __declspec(dllexport)
#else
#define ANTISOCIAL_API __declspec(dllimport)
#endif // ANTISOCIAL_EXPORT
#endif // __WIN32__

#ifdef __linux__
#define ANTISOCIAL_API
#endif // __LINUX__

#endif // ANTISOCIAL_H
