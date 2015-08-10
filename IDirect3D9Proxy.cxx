#include "IDirect3D9Proxy.hxx"
#include "IDirect3DDevice9ProxyHook.hxx"

IDirect3D9Proxy::IDirect3D9Proxy(IDirect3D9* pOriginal) : pOriginal(pOriginal) {}

IDirect3D9Proxy::~IDirect3D9Proxy() {}

HRESULT IDirect3D9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3D9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3D9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if (ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3D9Proxy::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return pOriginal->RegisterSoftwareDevice(pInitializeFunction);
}

UINT IDirect3D9Proxy::GetAdapterCount()
{
    return pOriginal->GetAdapterCount();
}

HRESULT IDirect3D9Proxy::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return pOriginal->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT IDirect3D9Proxy::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
    return pOriginal->GetAdapterModeCount(Adapter, Format);
}

HRESULT IDirect3D9Proxy::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
    return pOriginal->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT IDirect3D9Proxy::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
    return pOriginal->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT IDirect3D9Proxy::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
    return pOriginal->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT IDirect3D9Proxy::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
    return pOriginal->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT IDirect3D9Proxy::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
    return pOriginal->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT IDirect3D9Proxy::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
    return pOriginal->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT IDirect3D9Proxy::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
    return pOriginal->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT IDirect3D9Proxy::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
    return pOriginal->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR IDirect3D9Proxy::GetAdapterMonitor(UINT Adapter)
{
    return pOriginal->GetAdapterMonitor(Adapter);
}

HRESULT IDirect3D9Proxy::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
    HRESULT res = pOriginal->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
    if (res == D3D_OK)
    {
        *ppReturnedDeviceInterface = new IDirect3DDevice9ProxyHook(*ppReturnedDeviceInterface);
    }
    return res;
}
