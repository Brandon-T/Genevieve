#include "IDirect3DSwapChain9Proxy.hxx"

IDirect3DSwapChain9Proxy::IDirect3DSwapChain9Proxy(IDirect3DSwapChain9* pOriginal) : pOriginal(pOriginal) {}

IDirect3DSwapChain9Proxy::~IDirect3DSwapChain9Proxy() {}

HRESULT IDirect3DSwapChain9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3DSwapChain9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DSwapChain9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if (ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DSwapChain9Proxy::Present(const RECT* src_rect, const RECT* dst_rect, HWND dst_window, const RGNDATA* dirty_region, DWORD flags)
{
    return pOriginal->Present(src_rect, dst_rect, dst_window, dirty_region, flags);
}

HRESULT IDirect3DSwapChain9Proxy::GetFrontBufferData(IDirect3DSurface9 *pDestSurface)
{
    return pOriginal->GetFrontBufferData(pDestSurface);
}

HRESULT IDirect3DSwapChain9Proxy::GetBackBuffer(UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, struct IDirect3DSurface9** ppBackBuffer)
{
    return pOriginal->GetBackBuffer(iBackBuffer, Type, ppBackBuffer);
}

HRESULT IDirect3DSwapChain9Proxy::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
    return pOriginal->GetRasterStatus(pRasterStatus);
}

HRESULT IDirect3DSwapChain9Proxy::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
    return pOriginal->GetDisplayMode(pMode);
}

HRESULT IDirect3DSwapChain9Proxy::GetDevice(IDirect3DDevice9** ppDevice)
{
    return pOriginal->GetDevice(ppDevice);
}

HRESULT IDirect3DSwapChain9Proxy::GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return pOriginal->GetPresentParameters(pPresentationParameters);
}
