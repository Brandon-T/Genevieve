#include "Graphics.hxx"


#ifdef D3DX_SUPPORT
Font::Font(IDirect3DDevice9* pDevice, const char* name, unsigned short size) : fnt(nullptr), width(0), height(0)
{
    /*HDC DC = nullptr;
    IDirect3DSurface9* rt = nullptr;
    pDevice->GetRenderTarget(0, &rt);

    rt->GetDC(&DC);
    size = -MulDiv(size, GetDeviceCaps(DC, LOGPIXELSY), 72);
    rt->ReleaseDC(DC);*/

    HDC DC = GetDC(nullptr);
    D3DXCreateFontA(pDevice, -MulDiv(size, GetDeviceCaps(DC, LOGPIXELSY), 72), 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name, &fnt);
    ReleaseDC(nullptr, DC);

    IDirect3D9* d3d = nullptr;
    D3DDISPLAYMODE mode = {0};

    pDevice->GetDirect3D(&d3d);
    d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
    d3d->Release();

    width = mode.Width;
    height = mode.Height;
}
#endif

#ifdef D3DX_SUPPORT
Texture::Texture(IDirect3DDevice9* pDevice, const char* path, const D3DCOLOR colourkey) : tex(nullptr), pDevice(pDevice)
{
    D3DXCreateTextureFromFileEx(pDevice, path, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, colourkey, nullptr, nullptr, &tex);
}
#endif

Texture::Texture(IDirect3DDevice9* pDevice, int width, int height, const D3DFORMAT format) : tex(nullptr), pDevice(pDevice)
{
    pDevice->CreateTexture(width, height, 1, 0, format, D3DPOOL_MANAGED, &tex, 0);
}

std::uint8_t* Texture::Lock()
{
    D3DLOCKED_RECT rect;
    tex->LockRect(0, &rect, nullptr, D3DLOCK_DISCARD);
    return static_cast<std::uint8_t*>(rect.pBits);
}

void Texture::Unlock()
{
    tex->UnlockRect(0);
}

void Texture::GetDescription(D3DSURFACE_DESC* desc)
{
    tex->GetLevelDesc(0, desc);
}

void Texture::Draw(float X1, float Y1, float X2, float Y2)
{
    float UOffset = 0.5f / static_cast<float>(X2 - X1);
    float VOffset = 0.5f / static_cast<float>(Y2 - Y1);

    D3DVertex Vertices[] =
    {
        {X1, Y1, 1.0f, 1.0f, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF), 0.0f + UOffset, 0.0f + VOffset},
        {X2, Y1, 1.0f, 1.0f, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF), 1.0f + UOffset, 0.0f + VOffset},
        {X1, Y2, 1.0f, 1.0f, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF), 0.0f + UOffset, 1.0f + VOffset},
        {X2, Y2, 1.0f, 1.0f, D3DCOLOR_RGBA(0xFF, 0xFF, 0xFF, 0xFF), 1.0f + UOffset, 1.0f + VOffset}
    };

    pDevice->SetFVF(VERTEX_FVF_TEX);
    pDevice->SetTexture(0, tex);
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertices, sizeof(D3DVertex));
    pDevice->SetTexture(0, nullptr);
}

#ifdef D3DX_SUPPORT
Sprite::Sprite(IDirect3DDevice9* pDevice) : pDevice(pDevice)
{
    D3DXCreateSprite(pDevice, &spr);
}

void Sprite::Draw(IDirect3DTexture9* tex, D3DXVECTOR3* pos, const D3DCOLOR tint)
{
    D3DXVECTOR3 temp = D3DXVECTOR3(0, 0, 0);
    D3DXMATRIX world = {0}, rotation = {0}, scale = {0}, translation = {0};

    D3DXMatrixIdentity(&world);
    D3DXMatrixScaling(&scale, 1.0f, 1.0f, 1.0f);
    D3DXMatrixRotationYawPitchRoll(&rotation, 0.0f, 0.0f, 0.0f);
    D3DXMatrixTranslation(&translation, 0.0f, 0.0f, 0.0f);

    world = rotation * scale * translation;
    if (!pos) pos = &temp;

    spr->SetTransform(&world);
    spr->Begin(D3DXSPRITE_ALPHABLEND);
    spr->Draw(tex, nullptr, nullptr, pos, tint);
    spr->Flush();
    spr->End();
}
#endif
