#ifndef CONSOLE_HXX_INCLUDED
#define CONSOLE_HXX_INCLUDED

#include <iostream>
#include <windows.h>
#include <fstream>
#include <streambuf>

class Console
{
    private:
        void Swap(Console &console);
        std::wstreambuf *CinBuffer, *CoutBuffer, *CerrBuffer;
        std::wfstream ConsoleInput, ConsoleOutput, ConsoleError;

    public:
        Console();
        Console(const Console &console) = delete;
        Console(Console&& console);
        ~Console();

        template<typename T>
        Console& operator << (const T &Data) {std::wcout<<Data<<std::flush; return *this;}
};

#endif // CONSOLE_HXX_INCLUDED
