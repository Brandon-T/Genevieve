#ifndef EXPORT_HXX_INCLUDED
#define EXPORT_HXX_INCLUDED

#include "Memory.hxx"
#include "IDirect3D9Proxy.hxx"
#include <windows.h>
#include <memory>
#include <d3d9.h>

bool Initialise();


extern "C" {
    int __stdcall D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName);
    int __stdcall D3DPERF_EndEvent();
    DWORD __stdcall D3DPERF_GetStatus();
    WINBOOL __stdcall D3DPERF_QueryRepeatFrame();
    void __stdcall D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wsz);
    void __stdcall D3DPERF_SetOptions(DWORD dwOptions);
    void __stdcall D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wsz);
    void __stdcall DebugSetLevel();
    void __stdcall DebugSetMute();
    void __stdcall Direct3D9EnableMaximizedWindowedModeShim();
    IDirect3D9* __stdcall Direct3DCreate9(UINT SDKVersion);
    void __stdcall Direct3DCreate9Ex();
    void __stdcall Direct3DShaderValidatorCreate9();
    void __stdcall PSGPError();
    void __stdcall PSGPSampleTexture();
}

#endif // EXPORT_HXX_INCLUDED
