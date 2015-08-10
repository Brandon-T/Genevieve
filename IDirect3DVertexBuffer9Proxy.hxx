#ifndef IDIRECT3DVERTEXBUFFER9PROXY_HXX_INCLUDED
#define IDIRECT3DVERTEXBUFFER9PROXY_HXX_INCLUDED

#include <d3d9.h>
#include <cstdint>
#include <vector>
#include "Math.hxx"
#include "IDirect3DIndexBuffer9Proxy.hxx"

class IDirect3DVertexBuffer9Proxy : public IDirect3DVertexBuffer9
{
private:
    IDirect3DVertexBuffer9 *pOriginal;
    std::uint32_t Size;
    std::uint32_t FVF;

    std::size_t lockOffset;
    std::size_t lockSize;
    void *lockPointer;

    std::uint32_t ID;

public:
    IDirect3DVertexBuffer9Proxy(IDirect3DVertexBuffer9 *pOriginal, UINT Length, std::uint32_t FVF);
    virtual ~IDirect3DVertexBuffer9Proxy();

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
    HRESULT     __stdcall GetDesc(D3DVERTEXBUFFER_DESC *pDesc);


    inline IDirect3DVertexBuffer9* Original() {return pOriginal;}

    inline std::uint32_t GetID() const {return ID;}
    inline std::uint32_t GetFVF() const {return FVF;}

    std::vector<float> GetVertices(const IDirect3DIndexBuffer9Proxy* IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount) const;
    std::vector<std::uint8_t> GetColours(const IDirect3DIndexBuffer9Proxy* IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount) const;
};

#endif // IDIRECT3DVERTEXBUFFER9PROXY_HXX_INCLUDED
