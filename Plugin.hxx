#ifndef PLUGIN_HXX_INCLUDED
#define PLUGIN_HXX_INCLUDED

#include <d3d9.h>
#include "Graphics.hxx"

typedef void (*_SMARTGetMousePos)(int &x, int &y);
typedef void (*_SMARTSetCapture)(bool enabled);
typedef void (*_SMARTButtonPressed)(int id, bool state);

typedef struct
{
    int version;
    void *img, *dbg;
    int width, height;
    _SMARTGetMousePos getMousePos;
    _SMARTSetCapture setCapture;
} SMARTInfo;


extern "C" void SMARTPluginInit(SMARTInfo* ptr, bool* ReplaceButtons, int* ButtonCount, const char* const** ButtonText, const int** ButtonIDs, _SMARTButtonPressed* ButtonCallback);


bool SMARTIsValid();
bool SMARTIsCaptureEnabled();
bool SMARTIsDebugEnabled();
bool SMARTIsMinimised(IDirect3DDevice9 *device);
bool SMARTGetMousePosition(int &X, int &Y);

void SMARTNormaliseAlphaChannel();
void SMARTCaptureBackBuffer(IDirect3DDevice9* device, int &Width, int &Height, D3DFORMAT Format);
void SMARTDrawBackBuffer(IDirect3DDevice9* device);

#endif // PLUGIN_HXX_INCLUDED
