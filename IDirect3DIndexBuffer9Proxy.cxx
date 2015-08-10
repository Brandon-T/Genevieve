#include "IDirect3DIndexBuffer9Proxy.hxx"

IDirect3DIndexBuffer9Proxy::IDirect3DIndexBuffer9Proxy(IDirect3DIndexBuffer9 *pOriginal, UINT Length, D3DFORMAT Format) : pOriginal(pOriginal), Size(Length), Format(Format), ID(0)
{
}

IDirect3DIndexBuffer9Proxy::~IDirect3DIndexBuffer9Proxy() {}

HRESULT IDirect3DIndexBuffer9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3DIndexBuffer9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DIndexBuffer9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if(ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DIndexBuffer9Proxy::GetDevice(IDirect3DDevice9** ppDevice)
{
    return pOriginal->GetDevice(ppDevice);
}

HRESULT IDirect3DIndexBuffer9Proxy::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags)
{
    return pOriginal->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT IDirect3DIndexBuffer9Proxy::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
    return pOriginal->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT IDirect3DIndexBuffer9Proxy::FreePrivateData(REFGUID refguid)
{
    return pOriginal->FreePrivateData(refguid);
}

DWORD IDirect3DIndexBuffer9Proxy::SetPriority(DWORD PriorityNew)
{
    return pOriginal->SetPriority(PriorityNew);
}

DWORD IDirect3DIndexBuffer9Proxy::GetPriority()
{
    return pOriginal->GetPriority();
}

void IDirect3DIndexBuffer9Proxy::PreLoad()
{
    return pOriginal->PreLoad();
}

D3DRESOURCETYPE IDirect3DIndexBuffer9Proxy::GetType()
{
    return pOriginal->GetType();
}

HRESULT IDirect3DIndexBuffer9Proxy::Lock(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags)
{
    HRESULT res = pOriginal->Lock(OffsetToLock, SizeToLock, ppbData, Flags);

    if (ppbData && *ppbData)
    {
        this->lockOffset = OffsetToLock;
        this->lockSize = SizeToLock;
        this->lockPointer = *ppbData;
    }

    return res;
}

HRESULT IDirect3DIndexBuffer9Proxy::Unlock()
{
    if (this->lockPointer)
    {
    }
    return pOriginal->Unlock();
}

HRESULT IDirect3DIndexBuffer9Proxy::GetDesc(D3DINDEXBUFFER_DESC *pDesc)
{
    return pOriginal->GetDesc(pDesc);
}
