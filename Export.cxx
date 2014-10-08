#include "Export.hxx"

struct d3d_dll
{
    std::unique_ptr<Module> handle;
    FARPROC D3DPERF_BeginEvent;
    FARPROC D3DPERF_EndEvent;
    FARPROC D3DPERF_GetStatus;
    FARPROC D3DPERF_QueryRepeatFrame;
    FARPROC D3DPERF_SetMarker;
    FARPROC D3DPERF_SetOptions;
    FARPROC D3DPERF_SetRegion;
    FARPROC DebugSetLevel;
    FARPROC DebugSetMute;
    FARPROC Direct3D9EnableMaximizedWindowedModeShim;
    FARPROC Direct3DCreate9;
    FARPROC Direct3DCreate9Ex;
    FARPROC Direct3DShaderValidatorCreate9;
    FARPROC PSGPError;
    FARPROC PSGPSampleTexture;
} d3d;

bool Initialise()
{
    MessageBox(NULL, "HERE", "", 0);
    char Root[MAX_PATH];
    GetSystemDirectoryA(Root, MAX_PATH);
    #ifdef _MSC_VER
        strcat_s(Root, "\\d3d9.dll");
    #else
        strcat(Root, "\\d3d9.dll");
    #endif

    d3d.handle.reset(new Module(Root));
    if (d3d.handle->IsLoaded())
    {
        try
        {
            d3d.handle->AddressOf(d3d.D3DPERF_BeginEvent, "D3DPERF_BeginEvent");
            d3d.handle->AddressOf(d3d.D3DPERF_EndEvent, "D3DPERF_EndEvent");
            d3d.handle->AddressOf(d3d.D3DPERF_GetStatus, "D3DPERF_GetStatus");
            d3d.handle->AddressOf(d3d.D3DPERF_QueryRepeatFrame, "D3DPERF_QueryRepeatFrame");
            d3d.handle->AddressOf(d3d.D3DPERF_SetMarker, "D3DPERF_SetMarker");
            d3d.handle->AddressOf(d3d.D3DPERF_SetOptions, "D3DPERF_SetOptions");
            d3d.handle->AddressOf(d3d.D3DPERF_SetRegion, "D3DPERF_SetRegion");
            d3d.handle->AddressOf(d3d.DebugSetLevel, "DebugSetLevel");
            d3d.handle->AddressOf(d3d.DebugSetMute, "DebugSetMute");
            d3d.handle->AddressOf(d3d.Direct3DCreate9, "Direct3DCreate9");
            d3d.handle->AddressOf(d3d.Direct3DShaderValidatorCreate9, "Direct3DShaderValidatorCreate9");
            d3d.handle->AddressOf(d3d.PSGPError, "PSGPError");
            d3d.handle->AddressOf(d3d.PSGPSampleTexture, "PSGPSampleTexture");
            d3d.handle->AddressOf(d3d.Direct3DCreate9Ex, "Direct3DCreate9Ex");
            d3d.handle->AddressOf(d3d.Direct3D9EnableMaximizedWindowedModeShim, "Direct3D9EnableMaximizedWindowedModeShim");
            return true;
        }
        catch(std::exception &e)
        {
            CONSOLE_SCREEN_BUFFER_INFO Info;
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            GetConsoleScreenBufferInfo(hStdout, &Info);
            int Attributes = Info.wAttributes;
            SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::printf("\n\nDirect-X ERROR:  %s\n\n\n", e.what());
            SetConsoleTextAttribute(hStdout, Attributes);
        }
    }
    return false;
}

#ifndef _MSV_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif
int __stdcall D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
    return d3d.handle->Call<int>(d3d.D3DPERF_BeginEvent, col, wszName);
}

int __stdcall D3DPERF_EndEvent()
{
    return d3d.handle->Call<int>(d3d.D3DPERF_EndEvent);
}

DWORD __stdcall D3DPERF_GetStatus()
{
    return d3d.handle->Call<DWORD>(d3d.D3DPERF_GetStatus);
}

WINBOOL __stdcall D3DPERF_QueryRepeatFrame()
{
    return d3d.handle->Call<WINBOOL>(d3d.D3DPERF_QueryRepeatFrame);
}

void __stdcall D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wsz)
{
    d3d.handle->Call(d3d.D3DPERF_SetMarker, col, wsz);
}

void __stdcall D3DPERF_SetOptions(DWORD dwOptions)
{
    d3d.handle->Call(d3d.D3DPERF_SetOptions, dwOptions);
}

void __stdcall D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wsz)
{
    d3d.handle->Call(d3d.D3DPERF_SetRegion, col, wsz);
}

void __stdcall DebugSetLevel()
{
    d3d.handle->Call(d3d.DebugSetLevel);
}

void __stdcall DebugSetMute()
{
    d3d.handle->Call(d3d.DebugSetMute);
}

void __stdcall Direct3D9EnableMaximizedWindowedModeShim()
{
    d3d.handle->Call(d3d.Direct3D9EnableMaximizedWindowedModeShim);
}

IDirect3D9* __stdcall Direct3DCreate9(UINT SDKVersion)
{
    IDirect3D9* pOriginal = d3d.handle->Call<IDirect3D9*>(d3d.Direct3DCreate9, SDKVersion);
    return new IDirect3D9Proxy(pOriginal);
}

void __stdcall Direct3DCreate9Ex()
{
    d3d.handle->Call(d3d.Direct3DCreate9Ex);
}

void __stdcall Direct3DShaderValidatorCreate9()
{
    d3d.handle->Call(d3d.Direct3DShaderValidatorCreate9);
}

void __stdcall PSGPError()
{
    d3d.handle->Call(d3d.PSGPError);
}

void __stdcall PSGPSampleTexture()
{
    d3d.handle->Call(d3d.PSGPSampleTexture);
}
#ifndef _MSV_VER
#pragma GCC diagnostic pop
#endif
