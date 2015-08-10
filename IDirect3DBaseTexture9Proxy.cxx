#include "IDirect3DBaseTexture9Proxy.hxx"

IDirect3DBaseTexture9Proxy::IDirect3DBaseTexture9Proxy(IDirect3DBaseTexture9* pOriginal) : pOriginal(pOriginal) {}

IDirect3DBaseTexture9Proxy::~IDirect3DBaseTexture9Proxy() {}

HRESULT IDirect3DBaseTexture9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3DBaseTexture9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DBaseTexture9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if (ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DBaseTexture9Proxy::GetDevice(IDirect3DDevice9** ppDevice)
{
    return pOriginal->GetDevice(ppDevice);
}

HRESULT IDirect3DBaseTexture9Proxy::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags)
{
    return pOriginal->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT IDirect3DBaseTexture9Proxy::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
    return pOriginal->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT IDirect3DBaseTexture9Proxy::FreePrivateData(REFGUID refguid)
{
    return pOriginal->FreePrivateData(refguid);
}

DWORD IDirect3DBaseTexture9Proxy::SetPriority(DWORD PriorityNew)
{
    return pOriginal->SetPriority(PriorityNew);
}

DWORD IDirect3DBaseTexture9Proxy::GetPriority()
{
    return pOriginal->GetPriority();
}

void IDirect3DBaseTexture9Proxy::PreLoad()
{
    pOriginal->PreLoad();
}

D3DRESOURCETYPE IDirect3DBaseTexture9Proxy::GetType()
{
    return pOriginal->GetType();
}

DWORD IDirect3DBaseTexture9Proxy::SetLOD(DWORD LODNew)
{
    return pOriginal->SetLOD(LODNew);
}

DWORD IDirect3DBaseTexture9Proxy::GetLOD()
{
    return pOriginal->GetLOD();
}

DWORD IDirect3DBaseTexture9Proxy::GetLevelCount()
{
    return pOriginal->GetLevelCount();
}

HRESULT IDirect3DBaseTexture9Proxy::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
    return pOriginal->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE IDirect3DBaseTexture9Proxy::GetAutoGenFilterType()
{
    return pOriginal->GetAutoGenFilterType();
}

void IDirect3DBaseTexture9Proxy::GenerateMipSubLevels()
{
    pOriginal->GenerateMipSubLevels();
}
