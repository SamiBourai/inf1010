//! Fonction main
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 07 Mai 2020

#include <iostream>
#include "Tests.h"
#include "WindowsUnicodeConsole.h"

int main()
{
    initializeConsole();
    Tests::testAll();
}
