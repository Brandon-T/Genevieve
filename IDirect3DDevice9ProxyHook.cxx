#include "IDirect3DDevice9ProxyHook.hxx"

#ifdef D3DX_SUPPORT
D3DXVECTOR3 GetVertex(const std::uint8_t* vertices, std::int16_t index, std::uint16_t stride)
{
    D3DXVECTOR3 res;
    memcpy(&res.x, &vertices[index * stride], sizeof(float));
    memcpy(&res.y, &vertices[index * stride + sizeof(float)], sizeof(float));
    memcpy(&res.z, &vertices[index * stride + sizeof(float) * 2], sizeof(float));
    return res;
}
#else
Vec3 GetVertex(const std::uint8_t* vertices, std::int16_t index, std::uint16_t stride)
{
    Vec3 res;
    memcpy(&res.x, &vertices[index * stride], sizeof(float));
    memcpy(&res.y, &vertices[index * stride + sizeof(float)], sizeof(float));
    memcpy(&res.z, &vertices[index * stride + sizeof(float) * 2], sizeof(float));
    return res;
}
#endif // D3DX_SUPPORT


#ifdef D3DX_SUPPORT
void GetVertices(std::vector<D3DXVECTOR3> &verts, IDirect3DVertexBuffer9Proxy *VertexBuffer, IDirect3DIndexBuffer9Proxy *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride)
{
    const std::uint8_t* vertices = NULL;
    const std::uint16_t* indices = NULL;
    UINT EndIndex = StartIndex + (PrimCount * 3);

    vertices = reinterpret_cast<const std::uint8_t*>(VertexBuffer->InternalBuffer());
    indices = reinterpret_cast<const std::uint16_t*>(IndexBuffer->InternalBuffer()) + PrimCount * 3 * sizeof(std::uint16_t);
    verts.resize(EndIndex - StartIndex);

    for (UINT I = StartIndex, J = 0; I < EndIndex; ++I, ++J)
    {
        verts[J] = GetVertex(vertices, indices[I] + BaseVertexIndex, Stride);
    }
}
#else
void GetVertices(std::vector<Vec3> &verts, IDirect3DVertexBuffer9Proxy *VertexBuffer, IDirect3DIndexBuffer9Proxy *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride)
{
    /*const std::uint8_t* vertices = NULL;
    const std::uint16_t* indices = NULL;
    UINT EndIndex = StartIndex + (PrimCount * 3);

    vertices = reinterpret_cast<const std::uint8_t*>(VertexBuffer->InternalBuffer());
    indices = reinterpret_cast<const std::uint16_t*>(IndexBuffer->InternalBuffer()) + PrimCount * 3 * sizeof(std::uint16_t);
    verts.resize(EndIndex - StartIndex);

    for (UINT I = StartIndex, J = 0; I < EndIndex; ++I, ++J)
    {
        verts[J] = GetVertex(vertices, indices[I] + BaseVertexIndex, Stride);
    }*/
}
#endif // D3DX_SUPPORT


void IDirect3DDevice9ProxyHook::HandleMemory(bool AllocateImage)
{
}

void IDirect3DDevice9ProxyHook::HandleCommunication()
{
}

void IDirect3DDevice9ProxyHook::HandleDebugDrawing()
{
    if (font)
    {
         for (auto&& tex : textures)
        {
            font->Draw(tex.X, tex.Y, D3DCOLOR_XRGB(0, 0xFF, 0), "%", tex.ID);
        }

        for (auto&& mod : models)
        {
            font->Draw(mod.X, mod.Y, D3DCOLOR_XRGB(0xFF, 0, 0), "%", mod.ID);
        }
    }

    textures.clear();
    models.clear();
}


IDirect3DDevice9ProxyHook::IDirect3DDevice9ProxyHook(IDirect3DDevice9* pOriginal) : IDirect3DDevice9Proxy(pOriginal) {}

IDirect3DDevice9ProxyHook::~IDirect3DDevice9ProxyHook() {}

ULONG IDirect3DDevice9ProxyHook::AddRef()
{
    ++references;
    return IDirect3DDevice9ProxyHook::AddRef();
}

ULONG IDirect3DDevice9ProxyHook::Release()
{
    if (--references == 0)
    {
        font.reset(nullptr);
        pTexture = nullptr;
        pIndexBuffer = nullptr;
        pVertexBuffer = nullptr;
    }

    return IDirect3DDevice9ProxyHook::Release();
}



//Override rendering
HRESULT IDirect3DDevice9ProxyHook::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    if (pTexture)
    {
        //D3DXVECTOR3 vertex = WorldToScreen(pOriginal);
        //font->Draw(vertex.x, vertex.y, "%", curr->ID);
    }
    return IDirect3DDevice9Proxy::DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT IDirect3DDevice9ProxyHook::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
    if (pTexture && pIndexBuffer && pVertexBuffer && (primCount == 2 || NumVertices == 4))
    {
        if (PrimitiveType == D3DPT_TRIANGLELIST)
        {
            //Vec3 in = {(verts[0].x + verts[4].x) / 2.0f, (verts[0].y + verts[4].y) / 2.0f, 0};
        }
    }
    return IDirect3DDevice9Proxy::DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT IDirect3DDevice9ProxyHook::BeginScene()
{
    HRESULT res = IDirect3DDevice9Proxy::BeginScene();

    if (!font)
    {
        font.reset(new Font(this->Original(), "Arial", 8));

        #ifdef D3DX_SUPPORT
        IDirect3DDevice9Proxy::GetViewport(&ViewPort);
        IDirect3DDevice9Proxy::GetTransform(D3DTS_VIEW, &View);
        IDirect3DDevice9Proxy::GetTransform(D3DTS_PROJECTION, &Projection);
        IDirect3DDevice9Proxy::GetTransform(D3DTS_WORLD, &World);
        #else
        IDirect3DDevice9Proxy::GetViewport(&ViewPort);
        IDirect3DDevice9Proxy::GetTransform(D3DTS_VIEW, reinterpret_cast<D3DMATRIX*>(&View[0][0]));
        IDirect3DDevice9Proxy::GetTransform(D3DTS_PROJECTION, reinterpret_cast<D3DMATRIX*>(&Projection[0][0]));
        IDirect3DDevice9Proxy::GetTransform(D3DTS_WORLD, reinterpret_cast<D3DMATRIX*>(&World[0][0]));
        #endif // D3DX_SUPPORT
    }
    return res;
}

HRESULT IDirect3DDevice9ProxyHook::EndScene()
{
    HandleDebugDrawing();
    return IDirect3DDevice9Proxy::EndScene();
}

HRESULT IDirect3DDevice9ProxyHook::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    if (font)
        font->OnLostDevice();

    HRESULT res = IDirect3DDevice9Proxy::Reset(pPresentationParameters);

    if (font)
        font->OnResetDevice();

    return res;
}


//Override creations
HRESULT IDirect3DDevice9ProxyHook::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
    HRESULT res = IDirect3DDevice9Proxy::CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
    if (res == D3D_OK)
    {
        *pSwapChain = new IDirect3DSwapChain9Proxy(*pSwapChain);
    }
    return res;
}


HRESULT IDirect3DDevice9ProxyHook::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
    HRESULT res = IDirect3DDevice9Proxy::CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
    if (res == D3D_OK)
    {
        *ppTexture = new IDirect3DTexture9Proxy(*ppTexture, Width, Height, Format);
    }
    return res;
}

HRESULT IDirect3DDevice9ProxyHook::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
    HRESULT res = IDirect3DDevice9Proxy::CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
    if (res == D3D_OK)
    {
        *ppVertexBuffer = new IDirect3DVertexBuffer9Proxy(*ppVertexBuffer, Length, FVF);
    }
    return res;
}

HRESULT IDirect3DDevice9ProxyHook::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
    HRESULT res = IDirect3DDevice9Proxy::CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
    if (res == D3D_OK)
    {
        *ppIndexBuffer = new IDirect3DIndexBuffer9Proxy(*ppIndexBuffer, Length, Format);
    }
    return res;
}


//Override setters
HRESULT IDirect3DDevice9ProxyHook::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
    this->pTexture = nullptr;
    if (pTexture && pTexture->GetType() == D3DRTYPE_TEXTURE)
    {
        this->pTexture = static_cast<IDirect3DTexture9Proxy*>(pTexture);
        return IDirect3DDevice9Proxy::SetTexture(Stage, static_cast<IDirect3DTexture9Proxy*>(pTexture)->Original());
    }
    return IDirect3DDevice9Proxy::SetTexture(Stage, pTexture);
}

HRESULT IDirect3DDevice9ProxyHook::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
    this->pVertexBuffer = nullptr;
    if (pStreamData && pStreamData->GetType() == D3DRTYPE_VERTEXBUFFER)
    {
        this->pVertexBuffer = static_cast<IDirect3DVertexBuffer9Proxy*>(pStreamData);
        return IDirect3DDevice9Proxy::SetStreamSource(StreamNumber, static_cast<IDirect3DVertexBuffer9Proxy*>(pStreamData)->Original(), OffsetInBytes, Stride);
    }
    return IDirect3DDevice9Proxy::SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT IDirect3DDevice9ProxyHook::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    this->pIndexBuffer = nullptr;
    if (pIndexData && pIndexData->GetType() == D3DRTYPE_INDEXBUFFER)
    {
        this->pIndexBuffer = static_cast<IDirect3DIndexBuffer9Proxy*>(pIndexData);
        return IDirect3DDevice9Proxy::SetIndices(static_cast<IDirect3DIndexBuffer9Proxy*>(pIndexData)->Original());
    }
    return IDirect3DDevice9Proxy::SetIndices(pIndexData);
}


//Override consumers
HRESULT IDirect3DDevice9ProxyHook::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
    HRESULT res = IDirect3DDevice9Proxy::GetSwapChain(iSwapChain, pSwapChain);
    if (res == D3D_OK)
    {
        *pSwapChain = new IDirect3DSwapChain9Proxy(*pSwapChain);
    }
    return res;
}

HRESULT IDirect3DDevice9ProxyHook::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
    return IDirect3DDevice9Proxy::ProcessVertices(SrcStartIndex, DestIndex, VertexCount, static_cast<IDirect3DVertexBuffer9Proxy*>(pDestBuffer)->Original(), pVertexDecl, Flags);
}
