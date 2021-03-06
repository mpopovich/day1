// AppDay1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "..\lib\public.h"
#include "..\dll2\public.h"
#include <windows.h>

typedef double (CALLBACK* GetValuePtr)(int);

int main()
{
    std::cout << "Enter integer value: ";   
    int InputValue = 0;
    std::cin >> InputValue;

    // funkcije `get_value` iz static_library.lib (lib/public.h)
    double GotValue = static_lib::get_value(InputValue);
    std::cout << "Static lib - for input \"" << InputValue << "\" get_value returns: " << GotValue;

    // - funkcije `get_value` iz dynamic_library.dll (potpis: `double get_value(int)`)
    HMODULE Module = LoadLibraryA("D:\\CPP\\day1\\exercise\\01\\dll1\\x64\\Release\\dynamic_library.dll");

    if (Module != nullptr)
    {
      GetValuePtr GetValue = (GetValuePtr)GetProcAddress(Module, "get_value");

      if (GetValue)
      {
        GotValue = GetValue(InputValue);
        std::cout << "\nDll - for input \"" << InputValue << "\" get_value returns: " << GotValue;
      }

      FreeLibrary(Module);
    }

    // - funkcije `get_value` iz dynamic_library_with_implib.dll (dll2/public.h)
    GotValue = get_value(InputValue);
    std::cout << "\nDll with impl - for input \"" << InputValue << "\" get_value returns: " << GotValue;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
