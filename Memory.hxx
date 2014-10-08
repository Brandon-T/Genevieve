#ifndef MEMORY_HXX_INCLUDED
#define MEMORY_HXX_INCLUDED

#include <windows.h>
#include <string>
#include <stdexcept>

class Module
{
private:
    HMODULE module;

public:
    Module(const char* path) : module(LoadLibraryA(path)) {}
    Module(const wchar_t* path) : module(LoadLibraryW(path)) {}
    Module(const Module& other) = delete;
    Module(Module&& other) : module(other.module) {other.module = nullptr;}
    ~Module() {FreeLibrary(module);}

    explicit operator HMODULE() const {return module;}
    explicit operator bool() const {return module != nullptr;}
    bool IsLoaded() const {return module != nullptr;}

    template<typename T>
    T AddressOf(std::string FunctionName);

    template<typename T>
    bool AddressOf(T &FunctionDefinition, std::string FunctionName);

    template<typename... Args>
    void Call(void* func, Args... args);

    template<typename R, typename... Args>
    R Call(void* func, Args... args);

    template<typename... Args>
    void Call(FARPROC func, Args... args);

    template<typename R, typename... Args>
    R Call(FARPROC func, Args... args);
};

template<typename T>
T Module::AddressOf(std::string Name)
{
    T Result = reinterpret_cast<T>(GetProcAddress(module, Name.c_str()));
    return Result ? Result : throw std::runtime_error(Name);
}

template<typename T>
bool Module::AddressOf(T &Definition, std::string Name)
{
    return (Definition = AddressOf<T>(Name));
}

template<typename... Args>
void Module::Call(void* func, Args... args)
{
    return reinterpret_cast<void (__stdcall *)(Args...)>(func)(args...);
}

template<typename R, typename... Args>
R Module::Call(void* func, Args... args)
{
    return reinterpret_cast<R (__stdcall *)(Args...)>(func)(args...);
}

template<typename... Args>
void Module::Call(FARPROC func, Args... args)
{
    return reinterpret_cast<void (__stdcall *)(Args...)>(func)(args...);
}

template<typename R, typename... Args>
R Module::Call(FARPROC func, Args... args)
{
    return reinterpret_cast<R (__stdcall *)(Args...)>(func)(args...);
}

#endif // MEMORY_HXX_INCLUDED
