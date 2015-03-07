#include "Console.hxx"

Console::Console()
{
    if (AllocConsole())
    {
        CinBuffer = std::wcin.rdbuf();
        CoutBuffer = std::wcout.rdbuf();
        CerrBuffer = std::wcerr.rdbuf();
        ConsoleInput.open("CONIN$", std::ios::in);
        ConsoleOutput.open("CONOUT$", std::ios::out);
        ConsoleError.open("CONOUT$", std::ios::out);
        std::wcin.rdbuf(ConsoleInput.rdbuf());
        std::wcout.rdbuf(ConsoleOutput.rdbuf());
        std::wcerr.rdbuf(ConsoleError.rdbuf());
    }
}

Console::Console(Console &&console) : CinBuffer(nullptr), CoutBuffer(nullptr), CerrBuffer(nullptr)
{
    console.Swap(*this);
}

Console::~Console()
{
    ConsoleInput.close();
    ConsoleOutput.close();
    ConsoleError.close();
    std::wcin.rdbuf(CinBuffer);
    std::wcout.rdbuf(CoutBuffer);
    std::wcerr.rdbuf(CerrBuffer);
    FreeConsole();
}

void Console::Swap(Console &console)
{
    std::swap(CinBuffer, console.CinBuffer);
    std::swap(CoutBuffer, console.CoutBuffer);
    std::swap(CerrBuffer, console.CerrBuffer);
}
