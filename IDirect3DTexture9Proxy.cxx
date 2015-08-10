#include "IDirect3DTexture9Proxy.hxx"
#include <d3dx9.h>
#include <fstream>
#include "Math.hxx"

IDirect3DTexture9Proxy::IDirect3DTexture9Proxy(IDirect3DTexture9* pOriginal, std::uint32_t Width, std::uint32_t Height, D3DFORMAT Format) : pOriginal(pOriginal), ID(0), Width(Width), Height(Height), Format(Format) {}

IDirect3DTexture9Proxy::~IDirect3DTexture9Proxy() {}

HRESULT IDirect3DTexture9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3DTexture9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DTexture9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if (ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DTexture9Proxy::GetDevice(IDirect3DDevice9** ppDevice)
{
    return pOriginal->GetDevice(ppDevice);
}

HRESULT IDirect3DTexture9Proxy::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags)
{
    return pOriginal->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT IDirect3DTexture9Proxy::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
    return pOriginal->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT IDirect3DTexture9Proxy::FreePrivateData(REFGUID refguid)
{
    return pOriginal->FreePrivateData(refguid);
}

DWORD IDirect3DTexture9Proxy::SetPriority(DWORD PriorityNew)
{
    return pOriginal->SetPriority(PriorityNew);
}

DWORD IDirect3DTexture9Proxy::GetPriority()
{
    return pOriginal->GetPriority();
}

void IDirect3DTexture9Proxy::PreLoad()
{
    pOriginal->PreLoad();
}

D3DRESOURCETYPE IDirect3DTexture9Proxy::GetType()
{
    return pOriginal->GetType();
}

DWORD IDirect3DTexture9Proxy::SetLOD(DWORD LODNew)
{
    return pOriginal->SetLOD(LODNew);
}

DWORD IDirect3DTexture9Proxy::GetLOD()
{
    return pOriginal->GetLOD();
}

DWORD IDirect3DTexture9Proxy::GetLevelCount()
{
    return pOriginal->GetLevelCount();
}

HRESULT IDirect3DTexture9Proxy::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
    return pOriginal->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE IDirect3DTexture9Proxy::GetAutoGenFilterType()
{
    return pOriginal->GetAutoGenFilterType();
}

void IDirect3DTexture9Proxy::GenerateMipSubLevels()
{
    pOriginal->GenerateMipSubLevels();
}

HRESULT IDirect3DTexture9Proxy::GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc)
{
    return pOriginal->GetLevelDesc(Level, pDesc);
}

HRESULT IDirect3DTexture9Proxy::GetSurfaceLevel(UINT Level, IDirect3DSurface9** ppSurfaceLevel)
{
    return pOriginal->GetSurfaceLevel(Level, ppSurfaceLevel);
}

HRESULT IDirect3DTexture9Proxy::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, const RECT* pRect, DWORD Flags)
{
    return pOriginal->LockRect(Level, pLockedRect, pRect, Flags);
}

HRESULT IDirect3DTexture9Proxy::UnlockRect(UINT Level)
{
    HRESULT res = pOriginal->UnlockRect(Level);

    if (this->Width && this->Height)
    {
        D3DLOCKED_RECT lock;
        pOriginal->LockRect(0, &lock, nullptr, D3DLOCK_NOOVERWRITE | D3DLOCK_READONLY);
        this->ID = GVMath::ColourChecksum(lock.pBits, this->Width, this->Height);
        this->FID = GVMath::FullColourChecksum(lock.pBits, this->Width, this->Height);
        pOriginal->UnlockRect(0);
    }

    return res;
}

HRESULT IDirect3DTexture9Proxy::AddDirtyRect(const RECT* pDirtyRect)
{
    return pOriginal->AddDirtyRect(pDirtyRect);
}

void IDirect3DTexture9Proxy::Save()
{
    D3DLOCKED_RECT lock;
    if (pOriginal->LockRect(0, &lock, nullptr, D3DLOCK_READONLY) == D3D_OK)
    {
        char buff[256] = {0};
        sprintf(buff, "C:/Users/Kira/Desktop/Textures/%u.bmp", this->ID);
        Image{lock.pBits, Width, Height}.Save(buff);
        pOriginal->UnlockRect(0);
    }
}
