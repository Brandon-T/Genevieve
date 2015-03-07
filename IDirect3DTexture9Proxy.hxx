#ifndef IDIRECT3DTEXTURE9PROXY_HXX_INCLUDED
#define IDIRECT3DTEXTURE9PROXY_HXX_INCLUDED

#include <d3d9.h>

class IDirect3DTexture9Proxy : public IDirect3DTexture9
{
    private:
        IDirect3DTexture9* pOriginal;

    public:
        IDirect3DTexture9Proxy(IDirect3DTexture9* pOriginal);
        virtual ~IDirect3DTexture9Proxy();

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
        HRESULT  __stdcall GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc);
        HRESULT  __stdcall GetSurfaceLevel(UINT Level, IDirect3DSurface9** ppSurfaceLevel);
        HRESULT  __stdcall LockRect(UINT Level, D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags);
        HRESULT  __stdcall UnlockRect(UINT Level);
        HRESULT  __stdcall AddDirtyRect(CONST RECT* pDirtyRect);

        IDirect3DTexture9* Original() {return pOriginal;}
};

#endif // IDIRECT3DTEXTURE9PROXY_HXX_INCLUDED
