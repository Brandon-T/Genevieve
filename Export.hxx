#ifndef EXPORT_HXX_INCLUDED
#define EXPORT_HXX_INCLUDED

#include "Memory.hxx"
#include "IDirect3D9Proxy.hxx"
#include <windows.h>
#include <memory>
#include <d3d9.h>

bool Initialise();

#ifndef NO_ASM
extern "C" {
    void __stdcall DX_D3DPERF_BeginEvent();
    void __stdcall DX_D3DPERF_EndEvent();
    void __stdcall DX_D3DPERF_GetStatus();
    void __stdcall DX_D3DPERF_QueryRepeatFrame();
    void __stdcall DX_D3DPERF_SetMarker();
    void __stdcall DX_D3DPERF_SetOptions();
    void __stdcall DX_D3DPERF_SetRegion();
    void __stdcall DX_DebugSetLevel();
    void __stdcall DX_DebugSetMute();
    void __stdcall DX_Direct3D9EnableMaximizedWindowedModeShim();
    IDirect3D9* __stdcall DX_Direct3DCreate9(UINT SDKVersion);
    void __stdcall DX_Direct3DCreate9Ex();
    void __stdcall DX_Direct3DShaderValidatorCreate9();
    void __stdcall DX_PSGPError();
    void __stdcall DX_PSGPSampleTexture();
}
#else
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
#endif

#endif // EXPORT_HXX_INCLUDED
