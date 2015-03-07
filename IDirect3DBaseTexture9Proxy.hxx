#ifndef IDIRECT3DBASETEXTURE9PROXY_HXX_INCLUDED
#define IDIRECT3DBASETEXTURE9PROXY_HXX_INCLUDED

#include <d3d9.h>

class IDirect3DBaseTexture9Proxy : public IDirect3DBaseTexture9
{
    private:
        IDirect3DBaseTexture9* pOriginal;

    public:
        IDirect3DBaseTexture9Proxy(IDirect3DBaseTexture9* pOriginal);
        virtual ~IDirect3DBaseTexture9Proxy();

        HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj);
        ULONG    __stdcall AddRef();
        ULONG    __stdcall Release();
        HRESULT  __stdcall GetDevice(IDirect3DDevice9** ppDevice);
        HRESULT  __stdcall SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags);
        HRESULT  __stdcall GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData);
        HRESULT  __stdcall FreePrivateData(REFGUID refguid);
        DWORD    __stdcall SetPriority(DWORD PriorityNew);
        DWORD    __stdcall GetPriority();
        void     __stdcall PreLoad();
        D3DRESOURCETYPE __stdcall GetType();
        DWORD    __stdcall SetLOD(DWORD LODNew);
        DWORD    __stdcall GetLOD();
        DWORD    __stdcall GetLevelCount();
        HRESULT  __stdcall SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType);
        D3DTEXTUREFILTERTYPE __stdcall GetAutoGenFilterType();
        void     __stdcall GenerateMipSubLevels();
};

#endif // IDIRECT3DBASETEXTURE9PROXY_HXX_INCLUDED
