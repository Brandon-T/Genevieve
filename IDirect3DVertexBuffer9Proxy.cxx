#include "IDirect3DVertexBuffer9Proxy.hxx"


IDirect3DVertexBuffer9Proxy::IDirect3DVertexBuffer9Proxy(IDirect3DVertexBuffer9 *pOriginal, UINT Length, std::uint32_t FVF) : pOriginal(pOriginal), Size(Length), FVF(FVF), ID(0)
{
}

IDirect3DVertexBuffer9Proxy::~IDirect3DVertexBuffer9Proxy() {}

HRESULT IDirect3DVertexBuffer9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
    HRESULT hRes = pOriginal->QueryInterface(riid, ppvObj);
    *ppvObj = hRes == S_OK ? this : nullptr;
    return hRes;
}

ULONG IDirect3DVertexBuffer9Proxy::AddRef()
{
    return pOriginal->AddRef();
}

ULONG IDirect3DVertexBuffer9Proxy::Release()
{
    ULONG ReferenceCount = pOriginal->Release();
    if(ReferenceCount == 0)
    {
        delete this;
    }
    return ReferenceCount;
}

HRESULT IDirect3DVertexBuffer9Proxy::GetDevice(IDirect3DDevice9** ppDevice)
{
    return pOriginal->GetDevice(ppDevice);
}

HRESULT IDirect3DVertexBuffer9Proxy::SetPrivateData(REFGUID refguid, const void* pData, DWORD SizeOfData, DWORD Flags)
{
    return pOriginal->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT IDirect3DVertexBuffer9Proxy::GetPrivateData(REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
    return pOriginal->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT IDirect3DVertexBuffer9Proxy::FreePrivateData(REFGUID refguid)
{
    return pOriginal->FreePrivateData(refguid);
}

DWORD IDirect3DVertexBuffer9Proxy::SetPriority(DWORD PriorityNew)
{
    return pOriginal->SetPriority(PriorityNew);
}

DWORD IDirect3DVertexBuffer9Proxy::GetPriority()
{
    return pOriginal->GetPriority();
}

void IDirect3DVertexBuffer9Proxy::PreLoad()
{
    return pOriginal->PreLoad();
}

D3DRESOURCETYPE IDirect3DVertexBuffer9Proxy::GetType()
{
    return pOriginal->GetType();
}

HRESULT IDirect3DVertexBuffer9Proxy::Lock(UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags)
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

HRESULT IDirect3DVertexBuffer9Proxy::Unlock()
{
    if (this->lockPointer)
    {
    }
    return pOriginal->Unlock();
}

HRESULT IDirect3DVertexBuffer9Proxy::GetDesc(D3DVERTEXBUFFER_DESC *pDesc)
{
    return pOriginal->GetDesc(pDesc);
}

std::vector<float> IDirect3DVertexBuffer9Proxy::GetVertices(const IDirect3DIndexBuffer9Proxy* IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount) const
{
    std::vector<float> model_vertices;
    /*std::uint32_t stride = DXMath::CalculateStride(FVF);
    std::size_t EndIndex = StartIndex + (PrimCount * 3);
    const float* vertices = reinterpret_cast<const float*>(&data[0]);
    const std::uint16_t* indices = static_cast<const std::uint16_t*>(IndexBuffer->InternalBuffer()) + StartIndex;

    for (std::size_t i = StartIndex; i < EndIndex; ++i)
    {
        std::size_t offset = (indices[i] + BaseVertexIndex) * stride;

        model_vertices.emplace_back(vertices[offset]);
        model_vertices.emplace_back(vertices[offset + sizeof(float)]);
        model_vertices.emplace_back(vertices[offset + sizeof(float) * 2]);
    }*/

    return model_vertices;
}

std::vector<std::uint8_t> IDirect3DVertexBuffer9Proxy::GetColours(const IDirect3DIndexBuffer9Proxy* IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount) const
{
    std::vector<std::uint8_t> model_colours;
    /*std::uint32_t stride = DXMath::CalculateStride(FVF);
    std::size_t EndIndex = StartIndex + (PrimCount * 3);
    const std::uint8_t* colours = &data[0];
    const std::uint16_t* indices = static_cast<const std::uint16_t*>(IndexBuffer->InternalBuffer()) + StartIndex;

    for (std::size_t i = StartIndex; i < EndIndex; ++i)
    {
        std::size_t offset = (indices[i] + BaseVertexIndex) * stride;

        model_colours.emplace_back(colours[offset]);
        model_colours.emplace_back(colours[offset + sizeof(std::uint8_t)]);
        model_colours.emplace_back(colours[offset + sizeof(std::uint8_t) * 2]);
        model_colours.emplace_back(colours[offset + sizeof(std::uint8_t) * 3]);
    }*/

    return model_colours;
}

/*void IDirect3DVertexBuffer9Proxy::ProcessList(IDirect3DIndexBuffer9 *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride, void (*(&funcs)[4])(IDirect3DVertexBuffer9Proxy* vbo, void* buffer))
{
    if (!funcs) return;
    std::uint8_t* vertices = nullptr;
    std::uint16_t* indices = nullptr;
    UINT EndIndex = StartIndex + (PrimCount * 3);

    this->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
    IndexBuffer->Lock(0, PrimCount * 3 * sizeof(std::uint16_t), reinterpret_cast<void**>(&indices), 0);

    for (UINT I = StartIndex; I < EndIndex; ++I)
    {
        for (size_t J = 0; J < sizeof(funcs)/sizeof(funcs[0]); ++J)
        {
            funcs[J](this, &vertices[indices[I] + BaseVertexIndex]);
        }
    }

    IndexBuffer->Unlock();
    this->Unlock();
}

void IDirect3DVertexBuffer9Proxy::ProcessStrip(IDirect3DIndexBuffer9 *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride, void (*(&funcs)[4])(IDirect3DVertexBuffer9Proxy* vbo, void* buffer))
{
    if (!funcs) return;
    std::uint8_t* vertices = nullptr;
    std::uint16_t* indices = nullptr;
    UINT EndIndex = StartIndex + PrimCount;

    this->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
    IndexBuffer->Lock(0, PrimCount * 3 * sizeof(std::uint16_t), reinterpret_cast<void**>(&indices), 0);

    for (UINT I = StartIndex; I < EndIndex; ++I)
    {
        for (size_t J = 0; J < sizeof(funcs)/sizeof(funcs[0]); ++J)
        {
            funcs[J](this, &vertices[(indices[I] + BaseVertexIndex) * Stride]);
        }
    }

    IndexBuffer->Unlock();
    this->Unlock();
}

void IDirect3DVertexBuffer9Proxy::GetVertex(std::uint8_t* vertices, std::int16_t index, std::int32_t stride, D3DXVECTOR3 &vertex)
{
    memcpy(&vertex.x, &vertices[index * stride], sizeof(float));
    memcpy(&vertex.y, &vertices[index * stride + sizeof(float)], sizeof(float));
    memcpy(&vertex.z, &vertices[index * stride + sizeof(float) * 2], sizeof(float));
}*/
