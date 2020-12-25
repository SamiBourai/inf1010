/// Patch pour que la console Windows supporte l'affichage en UTF-8.
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef WINDOWSUNICODECONSOLE_H
#define WINDOWSUNICODECONSOLE_H

#ifdef _WIN32
#include <windows.h>
#endif

inline void initializeConsole()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

#endif // WINDOWSUNICODECONSOLE_H
