#include "Plugin.hxx"

const constexpr int DXButtonIDs[2] = {100, 101};
const constexpr char* DXButtonTexts[2] = {"Disable DirectX_Enable DirectX", "Enable DXDebug_Disable DXDebug"};

SMARTInfo* SmartGlobal = nullptr;
bool SMARTDebugEnabled = false;
bool SMARTCaptureEnabled = true;

template<typename T>
void SMARTSafeRelease(T* &Ptr)
{
    if (Ptr)
    {
        Ptr->Release();
        Ptr = nullptr;
    }
}

void SMARTButtonPressed(int ID, bool State)
{
    switch(ID)
    {
        case DXButtonIDs[0]:
            SmartGlobal->setCapture(!State);
            SMARTCaptureEnabled = State;
            break;

        case DXButtonIDs[1]:
            SMARTDebugEnabled = !State;
            break;

    }
}

void SMARTPluginInit(SMARTInfo* ptr, bool* ReplaceButtons, int* ButtonCount, const char* const** ButtonText, const int** ButtonIDs, _SMARTButtonPressed* ButtonCallback)
{
    SmartGlobal = ptr;
    if (ptr)
    {
        *ReplaceButtons = true;

        *ButtonCount = 2;
        *ButtonIDs = DXButtonIDs;
        *ButtonText = DXButtonTexts;
        *ButtonCallback = &SMARTButtonPressed;
    }
}

bool SMARTIsValid()
{
    return SmartGlobal && SmartGlobal->version;
}

bool SMARTIsCaptureEnabled()
{
    return SMARTCaptureEnabled;
}

bool SMARTIsDebugEnabled()
{
    return SMARTDebugEnabled;
}

bool SMARTGetMousePosition(int &X, int &Y)
{
    SmartGlobal->getMousePos(X, Y);
    return X > -1 && Y > -1;
}

bool SMARTIsMinimised(IDirect3DDevice9 *device)
{
    IDirect3DSurface9* RenderTarget = nullptr;
    HRESULT result = device->GetRenderTarget(0, &RenderTarget);

    if (result == D3D_OK)
    {
        HDC DC = nullptr;
        RenderTarget->GetDC(&DC);
        bool Minimised = IsIconic(WindowFromDC(DC));
        RenderTarget->ReleaseDC(DC);
        SMARTSafeRelease(RenderTarget);
        return Minimised;
    }
    return false;
}

void SMARTNormaliseAlphaChannel()
{
    std::uint8_t* Ptr = reinterpret_cast<std::uint8_t*>(SmartGlobal->dbg);
    for (int I = 0; I < SmartGlobal->height; ++I)
    {
        for (int J = 0; J < SmartGlobal->width; ++J)
        {
            std::uint8_t B = *(Ptr++);
            std::uint8_t G = *(Ptr++);
            std::uint8_t R = *(Ptr++);
            *(Ptr++) = (B == 0 && G == 0 && R == 0) ? 0 : 0xFF;
        }
    }
}

void SMARTCaptureBackBuffer(IDirect3DDevice9* device, int &Width, int &Height, D3DFORMAT Format)
{
    IDirect3DSurface9* RenderTarget = nullptr;
    IDirect3DSurface9* DestTarget = nullptr;
    HRESULT result = device->GetRenderTarget(0, &RenderTarget);

    if (result == D3D_OK)
    {
        if (Width == 0 || Height == 0 || Format == D3DFMT_UNKNOWN)
        {
            D3DSURFACE_DESC descriptor = {};
            RenderTarget->GetDesc(&descriptor);
            Width = descriptor.Width;
            Height = descriptor.Height;
            Format = descriptor.Format;
        }

        result = device->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SYSTEMMEM, &DestTarget, nullptr);
        result = device->GetRenderTargetData(RenderTarget, DestTarget);

        D3DLOCKED_RECT rect;
        DestTarget->LockRect(&rect, 0, D3DLOCK_READONLY);
        memcpy(SmartGlobal->img, rect.pBits, Width * Height * 4);
        DestTarget->UnlockRect();
    }

    SMARTSafeRelease(RenderTarget);
    SMARTSafeRelease(DestTarget);
}

void SMARTDrawBackBuffer(IDirect3DDevice9* device)
{
    SMARTNormaliseAlphaChannel();
    Texture texture = {device, SmartGlobal->width, SmartGlobal->height, D3DFMT_A8R8G8B8};
    memcpy(texture.Lock(), SmartGlobal->dbg, SmartGlobal->width * SmartGlobal->height * 4);
    texture.Unlock();
    texture.Draw(0, 0, SmartGlobal->width, SmartGlobal->height);
}
