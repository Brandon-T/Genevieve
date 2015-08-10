#ifndef IDIRECT3DINDEXBUFFER9PROXY_HXX_INCLUDED
#define IDIRECT3DINDEXBUFFER9PROXY_HXX_INCLUDED

#include <d3d9.h>
#include <cstdint>
#include <vector>
#include "Math.hxx"

class IDirect3DIndexBuffer9Proxy : public IDirect3DIndexBuffer9
{
private:
    IDirect3DIndexBuffer9 *pOriginal;
    std::uint32_t Size;
    D3DFORMAT Format;

    std::size_t lockOffset;
    std::size_t lockSize;
    void *lockPointer;

    std::uint32_t ID;

public:
    IDirect3DIndexBuffer9Proxy(IDirect3DIndexBuffer9* pOriginal, UINT Length, D3DFORMAT Format);
    virtual ~IDirect3DIndexBuffer9Proxy();

    HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj);
    ULONG    __stdcall AddRef();
    ULONG    __stdcall Release();
    HRESULT  __stdcall GetDevice(IDirect3DDevice9** ppDevice);
    HRESULT  __stdcall SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags);
    HRESULT  __stdcall GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
    HRESULT  __stdcall FreePrivateData(REFGUID refguid);
    DWORD    __stdcall SetPriority(DWORD PriorityNew);
    DWORD    __stdcall GetPriority();
    void     __stdcall PreLoad();
    D3DRESOURCETYPE __stdcall GetType();

    HRESULT     __stdcall Lock(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags);
    HRESULT     __stdcall Unlock();
    HRESULT     __stdcall GetDesc(D3DINDEXBUFFER_DESC *pDesc);

    inline IDirect3DIndexBuffer9* Original() {return pOriginal;}

    inline std::uint32_t GetID() const {return ID;}
    inline D3DFORMAT GetFormat() const {return Format;}
};

#endif // IDIRECT3DINDEXBUFFER9PROXY_HXX_INCLUDED
