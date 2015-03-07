#include "IDirect3DTexture9Proxy.hxx"

IDirect3DTexture9Proxy::IDirect3DTexture9Proxy(IDirect3DTexture9* pOriginal)
{
    this->pOriginal = pOriginal;
}

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

HRESULT IDirect3DTexture9Proxy::SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
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

HRESULT IDirect3DTexture9Proxy::LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
    return pOriginal->LockRect(Level, pLockedRect, pRect, Flags);
}

HRESULT IDirect3DTexture9Proxy::UnlockRect(UINT Level)
{
    return pOriginal->UnlockRect(Level);
}

HRESULT IDirect3DTexture9Proxy::AddDirtyRect(CONST RECT* pDirtyRect)
{
    return pOriginal->AddDirtyRect(pDirtyRect);
}
