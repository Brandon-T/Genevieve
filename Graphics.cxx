#include "Graphics.hxx"


//#ifdef D3DX_SUPPORT
Font::Font(IDirect3DDevice9* pDevice, const char* name, unsigned short size) : fnt(nullptr), width(0), height(0)
{
    /*HDC DC = nullptr;
    IDirect3DSurface9* rt = nullptr;
    pDevice->GetRenderTarget(0, &rt);

    rt->GetDC(&DC);
    size = -MulDiv(size, GetDeviceCaps(DC, LOGPIXELSY), 72);
    rt->ReleaseDC(DC);*/

    HDC DC = GetDC(nullptr);
    D3DXCreateFontA(pDevice, -MulDiv(size, GetDeviceCaps(DC, LOGPIXELSY), 72), 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name, &fnt);
    ReleaseDC(nullptr, DC);

    IDirect3D9* d3d = nullptr;
    D3DDISPLAYMODE mode = {0};

    pDevice->GetDirect3D(&d3d);
    d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
    d3d->Release();

    width = mode.Width;
    height = mode.Height;
}
//#endif

void Image::process_pixels(void* out, void* in)
{
    unsigned int i, j;
    BGRA* pOut = (BGRA*)out;
    unsigned char* pIn = (unsigned char*)in;

    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            pOut[(height - 1 - i) * width + j].B = *(pIn++);
            pOut[(height - 1 - i) * width + j].G = *(pIn++);
            pOut[(height - 1 - i) * width + j].R = *(pIn++);
            pOut[(height - 1 - i) * width + j].A = *(pIn++);
        }
    }
}

void Image::unprocess_pixels(void* out, void* in)
{
    unsigned int i, j;
    unsigned char* pOut = (unsigned char*)out;
    BGRA* pIn = (BGRA*)in;

    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            *(pOut++) = pIn[(height - 1 - i) * width + j].B;
            *(pOut++) = pIn[(height - 1 - i) * width + j].G;
            *(pOut++) = pIn[(height - 1 - i) * width + j].R;
            *(pOut++) = pIn[(height - 1 - i) * width + j].A;
        }
    }
}

Image::Image(void* pixels, unsigned int width, unsigned int height) : pixels(width > 0 && height > 0 ? malloc(((width * 32 + 31) / 32) * 4 * height) : nullptr), width(width > 0 ? width : 0), height(height > 0 ? height : 0)
{
    if (width > 0 && height > 0 && pixels)
    {
        process_pixels(this->pixels, pixels);
    }
}

bool Image::Save(const char* path)
{
    FILE* file = fopen(path, "wb");

    if (file)
    {
        unsigned short bpp = 32;
        unsigned int trash = 0;
        unsigned short planes = 1;
        unsigned int biSize = 108;
        unsigned int offset = 122;
        unsigned int compression = 3;
        unsigned short type = 0x4D42;
        unsigned int size = ((width * bpp + 31) / 32) * 4 * height;
        unsigned int bfSize = offset + size;
        unsigned int masks[4] = {0xFF0000, 0xFF00, 0xFF, 0xFF000000};
        unsigned int csType = 0x73524742;
        unsigned int epts[9] = {0};

        fwrite(&type, sizeof(type), 1, file);
        fwrite(&bfSize, sizeof(bfSize), 1, file);
        fwrite(&trash, sizeof(trash), 1, file);
        fwrite(&offset, sizeof(offset), 1, file);
        fwrite(&biSize, sizeof(biSize), 1, file);
        fwrite(&width, sizeof(width), 1, file);
        fwrite(&height, sizeof(height), 1, file);
        fwrite(&planes, sizeof(planes), 1, file);
        fwrite(&bpp, sizeof(bpp), 1, file);
        fwrite(&compression, sizeof(compression), 1, file);
        fwrite(&size, sizeof(size), 1, file);
        fwrite(&trash, sizeof(trash), 1, file);
        fwrite(&trash, sizeof(trash), 1, file);
        fwrite(&trash, sizeof(trash), 1, file);
        fwrite(&trash, sizeof(trash), 1, file);
        fwrite(&masks, sizeof(masks), 1, file);
        fwrite(&csType, sizeof(csType), 1, file);
        fwrite(&epts, sizeof(epts), 1, file);
        fwrite(&epts, sizeof(trash), 1, file);
        fwrite(&epts, sizeof(trash), 1, file);
        fwrite(&epts, sizeof(trash), 1, file);

        void* buffer = malloc(size);
        if (!buffer)
        {
            perror("Memory allocation failure.");
            return false;
        }

        unprocess_pixels(buffer, pixels);
        fwrite(pixels, 1, size, file);
        free(buffer);
        return true;
    }
    return false;
}

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

void Graphics::DrawCircle(float X, float Y, float Radius, D3DCOLOR Colour, int Resolution)
{
    D3DVertex Vertices[Resolution];

    for (int I = 0; I < Resolution; ++I)
    {
        Vertices[I].X = X + Radius * std::cos(3.141592654f * (I / (Resolution / 2.0f)));
        Vertices[I].Y = Y + Radius * std::sin(3.141592654f * (I / (Resolution / 2.0f)));
        Vertices[I].Z = 0.0f;
        Vertices[I].RHW = 1.0f;
        Vertices[I].Colour = Colour;
        Vertices[I].U = 0.0f;
        Vertices[I].V = 0.0f;
    }

    pDevice->SetFVF(VERTEX_FVF_TEX);
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, Resolution - 2, Vertices, sizeof(D3DVertex));
}
