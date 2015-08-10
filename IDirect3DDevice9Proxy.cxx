#include "IDirect3DDevice9Proxy.hxx"

IDirect3DDevice9Proxy::IDirect3DDevice9Proxy(IDirect3DDevice9* pOriginal) : pOriginal(pOriginal) {}

IDirect3DDevice9Proxy::~IDirect3DDevice9Proxy() {}

HRESULT IDirect3DDevice9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    return pOriginal->QueryInterface(riid, ppvObj);
}

ULONG IDirect3DDevice9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DDevice9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if (ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DDevice9Proxy::TestCooperativeLevel()
{
    return pOriginal->TestCooperativeLevel();
}

UINT IDirect3DDevice9Proxy::GetAvailableTextureMem()
{
    return pOriginal->GetAvailableTextureMem();
}

HRESULT IDirect3DDevice9Proxy::EvictManagedResources()
{
    return pOriginal->EvictManagedResources();
}

HRESULT IDirect3DDevice9Proxy::GetDirect3D(IDirect3D9** ppD3D9)
{
    return pOriginal->GetDirect3D(ppD3D9);
}

HRESULT IDirect3DDevice9Proxy::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return pOriginal->GetDeviceCaps(pCaps);
}

HRESULT IDirect3DDevice9Proxy::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
    return pOriginal->GetDisplayMode(iSwapChain, pMode);
}

HRESULT IDirect3DDevice9Proxy::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return pOriginal->GetCreationParameters(pParameters);
}

HRESULT IDirect3DDevice9Proxy::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
    return pOriginal->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void IDirect3DDevice9Proxy::SetCursorPosition(int X, int Y, DWORD Flags)
{
    return pOriginal->SetCursorPosition(X, Y, Flags);
}

BOOL IDirect3DDevice9Proxy::ShowCursor(BOOL bShow)
{
    return pOriginal->ShowCursor(bShow);
}

HRESULT IDirect3DDevice9Proxy::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
    return pOriginal->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT IDirect3DDevice9Proxy::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
    return pOriginal->GetSwapChain(iSwapChain, pSwapChain);
}

UINT IDirect3DDevice9Proxy::GetNumberOfSwapChains()
{
    return pOriginal->GetNumberOfSwapChains();
}

HRESULT IDirect3DDevice9Proxy::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return pOriginal->Reset(pPresentationParameters);
}

HRESULT IDirect3DDevice9Proxy::Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    return pOriginal->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT IDirect3DDevice9Proxy::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
    return pOriginal->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT IDirect3DDevice9Proxy::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
    return pOriginal->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT IDirect3DDevice9Proxy::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return pOriginal->SetDialogBoxMode(bEnableDialogs);
}

void IDirect3DDevice9Proxy::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp)
{
    return pOriginal->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void IDirect3DDevice9Proxy::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
    return pOriginal->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT IDirect3DDevice9Proxy::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
    return pOriginal->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
    return pOriginal->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
    return pOriginal->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
    return pOriginal->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
    return pOriginal->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return pOriginal->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return pOriginal->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint)
{
    return pOriginal->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT IDirect3DDevice9Proxy::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
    return pOriginal->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT IDirect3DDevice9Proxy::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
    return pOriginal->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT IDirect3DDevice9Proxy::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
    return pOriginal->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT IDirect3DDevice9Proxy::StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
    return pOriginal->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT IDirect3DDevice9Proxy::ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color)
{
    return pOriginal->ColorFill(pSurface, pRect, color);
}

HRESULT IDirect3DDevice9Proxy::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return pOriginal->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT IDirect3DDevice9Proxy::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
    return pOriginal->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT IDirect3DDevice9Proxy::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
    return pOriginal->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT IDirect3DDevice9Proxy::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
    return pOriginal->SetDepthStencilSurface(pNewZStencil);
}

HRESULT IDirect3DDevice9Proxy::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
    return pOriginal->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT IDirect3DDevice9Proxy::BeginScene()
{
    return pOriginal->BeginScene();
}

HRESULT IDirect3DDevice9Proxy::EndScene()
{
    return pOriginal->EndScene();
}

HRESULT IDirect3DDevice9Proxy::Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
    return pOriginal->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT IDirect3DDevice9Proxy::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
    return pOriginal->SetTransform(State, pMatrix);
}

HRESULT IDirect3DDevice9Proxy::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
    return pOriginal->GetTransform(State, pMatrix);
}

HRESULT IDirect3DDevice9Proxy::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
    return pOriginal->MultiplyTransform(State, pMatrix);
}

HRESULT IDirect3DDevice9Proxy::SetViewport(const D3DVIEWPORT9* pViewport)
{
    return pOriginal->SetViewport(pViewport);
}

HRESULT IDirect3DDevice9Proxy::GetViewport(D3DVIEWPORT9* pViewport)
{
    return pOriginal->GetViewport(pViewport);
}

HRESULT IDirect3DDevice9Proxy::SetMaterial(const D3DMATERIAL9* pMaterial)
{
    return pOriginal->SetMaterial(pMaterial);
}

HRESULT IDirect3DDevice9Proxy::GetMaterial(D3DMATERIAL9* pMaterial)
{
    return pOriginal->GetMaterial(pMaterial);
}

HRESULT IDirect3DDevice9Proxy::SetLight(DWORD Index, const D3DLIGHT9* pLight)
{
    return pOriginal->SetLight(Index, pLight);
}

HRESULT IDirect3DDevice9Proxy::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
    return pOriginal->GetLight(Index, pLight);
}

HRESULT IDirect3DDevice9Proxy::LightEnable(DWORD Index, BOOL Enable)
{
    return pOriginal->LightEnable(Index, Enable);
}

HRESULT IDirect3DDevice9Proxy::GetLightEnable(DWORD Index, BOOL* pEnable)
{
    return pOriginal->GetLightEnable(Index, pEnable);
}

HRESULT IDirect3DDevice9Proxy::SetClipPlane(DWORD Index, const float* pPlane)
{
    return pOriginal->SetClipPlane(Index, pPlane);
}

HRESULT IDirect3DDevice9Proxy::GetClipPlane(DWORD Index, float* pPlane)
{
    return pOriginal->GetClipPlane(Index, pPlane);
}

HRESULT IDirect3DDevice9Proxy::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
    return pOriginal->SetRenderState(State, Value);
}

HRESULT IDirect3DDevice9Proxy::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
    return pOriginal->GetRenderState(State, pValue);
}

HRESULT IDirect3DDevice9Proxy::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
    return pOriginal->CreateStateBlock(Type, ppSB);
}

HRESULT IDirect3DDevice9Proxy::BeginStateBlock()
{
    return pOriginal->BeginStateBlock();
}

HRESULT IDirect3DDevice9Proxy::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
    return pOriginal->EndStateBlock(ppSB);
}

HRESULT IDirect3DDevice9Proxy::SetClipStatus(const D3DCLIPSTATUS9* pClipStatus)
{
    return pOriginal->SetClipStatus(pClipStatus);
}

HRESULT IDirect3DDevice9Proxy::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return pOriginal->GetClipStatus(pClipStatus);
}

HRESULT IDirect3DDevice9Proxy::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
    return pOriginal->GetTexture(Stage, ppTexture);
}

HRESULT IDirect3DDevice9Proxy::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
    return pOriginal->SetTexture(Stage, pTexture);
}

HRESULT IDirect3DDevice9Proxy::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
    return pOriginal->GetTextureStageState(Stage, Type, pValue);
}

HRESULT IDirect3DDevice9Proxy::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    return pOriginal->SetTextureStageState(Stage, Type, Value);
}

HRESULT IDirect3DDevice9Proxy::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
    return pOriginal->GetSamplerState(Sampler, Type, pValue);
}

HRESULT IDirect3DDevice9Proxy::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
    return pOriginal->SetSamplerState(Sampler, Type, Value);
}

HRESULT IDirect3DDevice9Proxy::ValidateDevice(DWORD* pNumPasses)
{
    return pOriginal->ValidateDevice(pNumPasses);
}

HRESULT IDirect3DDevice9Proxy::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries)
{
    return pOriginal->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT IDirect3DDevice9Proxy::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
    return pOriginal->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT IDirect3DDevice9Proxy::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return pOriginal->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT IDirect3DDevice9Proxy::GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return pOriginal->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT IDirect3DDevice9Proxy::SetScissorRect(const RECT* pRect)
{
    return pOriginal->SetScissorRect(pRect);
}

HRESULT IDirect3DDevice9Proxy::GetScissorRect(RECT* pRect)
{
    return pOriginal->GetScissorRect(pRect);
}

HRESULT IDirect3DDevice9Proxy::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return pOriginal->SetSoftwareVertexProcessing(bSoftware);
}

BOOL IDirect3DDevice9Proxy::GetSoftwareVertexProcessing()
{
    return pOriginal->GetSoftwareVertexProcessing();
}

HRESULT IDirect3DDevice9Proxy::SetNPatchMode(float nSegments)
{
    return pOriginal->SetNPatchMode(nSegments);
}

float IDirect3DDevice9Proxy::GetNPatchMode()
{
    return pOriginal->GetNPatchMode();
}

HRESULT IDirect3DDevice9Proxy::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    return pOriginal->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT IDirect3DDevice9Proxy::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
    return pOriginal->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT IDirect3DDevice9Proxy::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return pOriginal->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT IDirect3DDevice9Proxy::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return pOriginal->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT IDirect3DDevice9Proxy::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
    return pOriginal->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT IDirect3DDevice9Proxy::CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
    return pOriginal->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT IDirect3DDevice9Proxy::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
    return pOriginal->SetVertexDeclaration(pDecl);
}

HRESULT IDirect3DDevice9Proxy::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
    return pOriginal->GetVertexDeclaration(ppDecl);
}

HRESULT IDirect3DDevice9Proxy::SetFVF(DWORD FVF)
{
    return pOriginal->SetFVF(FVF);
}

HRESULT IDirect3DDevice9Proxy::GetFVF(DWORD* pFVF)
{
    return pOriginal->GetFVF(pFVF);
}

HRESULT IDirect3DDevice9Proxy::CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
    return pOriginal->CreateVertexShader(pFunction, ppShader);
}

HRESULT IDirect3DDevice9Proxy::SetVertexShader(IDirect3DVertexShader9* pShader)
{
    return pOriginal->SetVertexShader(pShader);
}

HRESULT IDirect3DDevice9Proxy::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
    return pOriginal->GetVertexShader(ppShader);
}

HRESULT IDirect3DDevice9Proxy::SetVertexShaderConstantF(UINT StartRegister, const float* pconstantData, UINT Vector4fCount)
{
    return pOriginal->SetVertexShaderConstantF(StartRegister, pconstantData, Vector4fCount);
}

HRESULT IDirect3DDevice9Proxy::GetVertexShaderConstantF(UINT StartRegister, float* pconstantData, UINT Vector4fCount)
{
    return pOriginal->GetVertexShaderConstantF(StartRegister, pconstantData, Vector4fCount);
}

HRESULT IDirect3DDevice9Proxy::SetVertexShaderConstantI(UINT StartRegister, const int* pconstantData, UINT Vector4iCount)
{
    return pOriginal->SetVertexShaderConstantI(StartRegister, pconstantData, Vector4iCount);
}

HRESULT IDirect3DDevice9Proxy::GetVertexShaderConstantI(UINT StartRegister, int* pconstantData, UINT Vector4iCount)
{
    return pOriginal->GetVertexShaderConstantI(StartRegister, pconstantData, Vector4iCount);
}

HRESULT IDirect3DDevice9Proxy::SetVertexShaderConstantB(UINT StartRegister, const BOOL* pconstantData, UINT BoolCount)
{
    return pOriginal->SetVertexShaderConstantB(StartRegister, pconstantData, BoolCount);
}

HRESULT IDirect3DDevice9Proxy::GetVertexShaderConstantB(UINT StartRegister, BOOL* pconstantData, UINT BoolCount)
{
    return pOriginal->GetVertexShaderConstantB(StartRegister, pconstantData, BoolCount);
}

HRESULT IDirect3DDevice9Proxy::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
    return pOriginal->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT IDirect3DDevice9Proxy::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
    return pOriginal->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT IDirect3DDevice9Proxy::SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
    return pOriginal->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT IDirect3DDevice9Proxy::GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)
{
    return pOriginal->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT IDirect3DDevice9Proxy::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    return pOriginal->SetIndices(pIndexData);
}

HRESULT IDirect3DDevice9Proxy::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
    return pOriginal->GetIndices(ppIndexData);
}

HRESULT IDirect3DDevice9Proxy::CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
    return pOriginal->CreatePixelShader(pFunction, ppShader);
}

HRESULT IDirect3DDevice9Proxy::SetPixelShader(IDirect3DPixelShader9* pShader)
{
    return pOriginal->SetPixelShader(pShader);
}

HRESULT IDirect3DDevice9Proxy::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
    return pOriginal->GetPixelShader(ppShader);
}

HRESULT IDirect3DDevice9Proxy::SetPixelShaderConstantF(UINT StartRegister, const float* pconstantData, UINT Vector4fCount)
{
    return pOriginal->SetPixelShaderConstantF(StartRegister, pconstantData, Vector4fCount);
}

HRESULT IDirect3DDevice9Proxy::GetPixelShaderConstantF(UINT StartRegister, float* pconstantData, UINT Vector4fCount)
{
    return pOriginal->GetPixelShaderConstantF(StartRegister, pconstantData, Vector4fCount);
}

HRESULT IDirect3DDevice9Proxy::SetPixelShaderConstantI(UINT StartRegister, const int* pconstantData, UINT Vector4iCount)
{
    return pOriginal->SetPixelShaderConstantI(StartRegister, pconstantData, Vector4iCount);
}

HRESULT IDirect3DDevice9Proxy::GetPixelShaderConstantI(UINT StartRegister, int* pconstantData, UINT Vector4iCount)
{
    return pOriginal->GetPixelShaderConstantI(StartRegister, pconstantData, Vector4iCount);
}

HRESULT IDirect3DDevice9Proxy::SetPixelShaderConstantB(UINT StartRegister, const BOOL* pconstantData, UINT BoolCount)
{
    return pOriginal->SetPixelShaderConstantB(StartRegister, pconstantData, BoolCount);
}

HRESULT IDirect3DDevice9Proxy::GetPixelShaderConstantB(UINT StartRegister, BOOL* pconstantData, UINT BoolCount)
{
    return pOriginal->GetPixelShaderConstantB(StartRegister, pconstantData, BoolCount);
}

HRESULT IDirect3DDevice9Proxy::DrawRectPatch(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return pOriginal->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT IDirect3DDevice9Proxy::DrawTriPatch(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return pOriginal->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT IDirect3DDevice9Proxy::DeletePatch(UINT Handle)
{
    return pOriginal->DeletePatch(Handle);
}

HRESULT IDirect3DDevice9Proxy::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
    return pOriginal->CreateQuery(Type, ppQuery);
}
