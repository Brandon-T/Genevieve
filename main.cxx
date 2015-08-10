#include "Memory.hxx"
#include "Graphics.hxx"
#include "Math.hxx"
#include "Export.hxx"

#include <fstream>
#include <memory>


/*D3DXVECTOR3 GetVertex(std::uint8_t *vertices, std::int16_t index, std::uint16_t stride)
{
    D3DXVECTOR3 res = {0};
    memcpy(&res.x, &vertices[index * stride], sizeof(float));
    memcpy(&res.y, &vertices[index * stride + sizeof(float)], sizeof(float));
    memcpy(&res.z, &vertices[index * stride + sizeof(float) * 2], sizeof(float));
    return res;
}

void ProcessTriangleList(IDirect3DVertexBuffer9 *VertexBuffer, IDirect3DIndexBuffer9 *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride)
{
    std::uint8_t *vertices = NULL;
    std::uint16_t *indices = NULL;
    UINT EndIndex = StartIndex + (PrimCount * 3);

    VertexBuffer->Lock(0, 0, reinterpret_cast<void **>(&vertices), 0);
    IndexBuffer->Lock(0, PrimCount * 3 * sizeof(std::uint16_t), reinterpret_cast<void **>(&indices), 0);

    for (UINT I = StartIndex; I < EndIndex; ++I)
    {
        //D3DXVECTOR3 v = GetVertex(vertices, indices[I] + BaseVertexIndex, Stride); //store it somewhere.. check for duplicates in the storage..
    }

    IndexBuffer->Unlock();
    VertexBuffer->Unlock();
}

void ProcessTriangleStrip(IDirect3DVertexBuffer9 *VertexBuffer, IDirect3DIndexBuffer9 *IndexBuffer, std::uint32_t BaseVertexIndex, std::uint32_t StartIndex, std::uint32_t PrimCount, std::uint32_t Stride)
{
    std::uint8_t *vertices = NULL;
    std::uint16_t *indices = NULL;
    UINT EndIndex = StartIndex + PrimCount;

    VertexBuffer->Lock(0, 0, reinterpret_cast<void **>(&vertices), 0);
    IndexBuffer->Lock(0, PrimCount * 3 * sizeof(std::uint16_t), reinterpret_cast<void **>(&indices), 0);

    for (UINT I = StartIndex; I < EndIndex; ++I)
    {
        //GetVertex(vertices, indices[I] + BaseVertexIndex, Stride); //store it somewhere.. check for duplicates in the storage..
    }

    IndexBuffer->Unlock();
    VertexBuffer->Unlock();
}

D3DXVECTOR3 WorldToScreen(IDirect3DDevice9* pDevice, D3DXVECTOR3 in = D3DXVECTOR3(0, 0, 0))
{
	D3DXMATRIX wvp;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 out;

    pDevice->GetViewport(&vp);
	pDevice->GetVertexShaderConstantF(0, reinterpret_cast<float*>(&wvp), 4);
	D3DXMatrixTranspose(&wvp, &wvp);
	D3DXVec3TransformCoord(&out, &in, &wvp);
    return D3DXVECTOR3((out.x + 1.0f) * vp.Width * 0.5f + vp.X, (1.0f - out.y) * vp.Height * 0.5f + vp.Y, out.z);
}

D3DXVECTOR3 WorldToScreen2(IDirect3DDevice9* pDevice, D3DXVECTOR3 in = D3DXVECTOR3(0, 0, 0))
{
    D3DVIEWPORT9 vp;
    D3DXVECTOR3 out;
    D3DXMATRIX proj, view, world;

    pDevice->GetViewport(&vp);
    pDevice->GetTransform(D3DTS_VIEW, &view);
    pDevice->GetTransform(D3DTS_PROJECTION, &proj);
    pDevice->GetTransform(D3DTS_WORLD, &world);
    D3DXVec3Project(&out, &in, &vp, &proj, &view, &world);
    return out;
}

D3DXVECTOR3 WorldToScreen3(IDirect3DDevice9* pDevice, D3DXVECTOR3 in = D3DXVECTOR3(0, 0, 0))
{
    D3DVIEWPORT9 vp;
    D3DXVECTOR3 out;
    D3DXMATRIX proj, view, world;

    D3DXMatrixIdentity(&world);
    pDevice->GetViewport(&vp);
	pDevice->GetVertexShaderConstantF(0, proj, 4);
	pDevice->GetVertexShaderConstantF(231, view, 4);
	D3DXVec3Project(&out, &in, &vp, &proj, &view, &world);
	return out;
}

bool DisassembleShader(IDirect3DDevice9* pDevice, const char* path)
{
    #ifndef _MSC_VER
    static Module mod("D3DX9_40.dll");
    static HRESULT (*D3DXDisassembleShader)(const DWORD*, BOOL, LPCSTR, LPD3DXBUFFER*) = NULL;

    if (!mod || !mod.AddressOf(D3DXDisassembleShader, "D3DXDisassembleShader"))
        return false;
    #endif

    std::fstream file(path);
    if (file)
    {
        IDirect3DVertexShader9* pShader = nullptr;
        if (pDevice->GetVertexShader(&pShader) == D3D_OK)
        {
            UINT size = 0;
            ID3DXBuffer* out = nullptr;
            pShader->GetFunction(nullptr, &size);
            std::unique_ptr<std::uint8_t> pData(new std::uint8_t[size]);
            pShader->GetFunction(pData.get(), &size);
            pShader->Release();

            if (D3DXDisassembleShader(reinterpret_cast<DWORD*>(pData.get()), false, nullptr, &out) == D3D_OK)
            {
                file.write(static_cast<const char*>(out->GetBufferPointer()), out->GetBufferSize());
                file << std::endl;
                return true;
            }
        }
    }

    return false;
}

bool SaveTexture(IDirect3DDevice9* pDevice, const char* path)
{
    IDirect3DBaseTexture9* basetex = nullptr;
    if (pDevice->GetTexture(0, &basetex) == D3D_OK)
    {
        D3DSURFACE_DESC desc;
        IDirect3DTexture9* tex = static_cast<IDirect3DTexture9*>(basetex);
        tex->GetLevelDesc(0, &desc);

        if (desc.Width > 0 && desc.Height > 0)
        {
            if (D3DXSaveTextureToFile(path, D3DXIFF_PNG, tex, nullptr) == D3D_OK)
            {
                basetex->Release();
                return true;
            }
        }

        basetex->Release();
    }
    return false;
}*/

__attribute__((constructor)) void __load()
{
    Initialise();
}

__attribute__((destructor)) void __unload()
{
}
