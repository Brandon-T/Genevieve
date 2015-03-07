#ifndef IDIRECT3DSWAPCHAINPROXY_HXX_INCLUDED
#define IDIRECT3DSWAPCHAINPROXY_HXX_INCLUDED

#include <d3d9.h>

class IDirect3DSwapChain9Proxy : public IDirect3DSwapChain9
{
    private:
        IDirect3DSwapChain9* pOriginal;

    public:
        IDirect3DSwapChain9Proxy(IDirect3DSwapChain9* pOriginal);
        virtual ~IDirect3DSwapChain9Proxy();

        HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj);
        ULONG    __stdcall AddRef();
        ULONG    __stdcall Release();
        HRESULT  __stdcall Present(const RECT* src_rect, const RECT* dst_rect, HWND dst_window, const RGNDATA* dirty_region, DWORD flags);
        HRESULT  __stdcall GetFrontBufferData(IDirect3DSurface9 *pDestSurface);
        HRESULT  __stdcall GetBackBuffer(UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, struct IDirect3DSurface9** ppBackBuffer);
        HRESULT  __stdcall GetRasterStatus(D3DRASTER_STATUS* pRasterStatus);
        HRESULT  __stdcall GetDisplayMode(D3DDISPLAYMODE* pMode);
        HRESULT  __stdcall GetDevice(IDirect3DDevice9** ppDevice);
        HRESULT  __stdcall GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters);
};

#endif // IDIRECT3DSWAPCHAINPROXY_HXX_INCLUDED
