#ifndef GRAPHICS_HXX_INCLUDED
#define GRAPHICS_HXX_INCLUDED

#include <d3d9.h>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

#ifdef D3DX_SUPPORT
#include <d3dx9.h>
#endif



#define VERTEX_FVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define VERTEX_FVF_TEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef union BGRA
{
    struct {std::uint8_t B, G, R, A;};
    std::uint32_t Colour;
} *PBGRA;

typedef union RGBA
{
    struct {std::uint8_t R, G, B, A;};
    std::uint32_t Colour;
} *PRGBA;

typedef union ARGB
{
    struct{std::uint8_t A, R, G, B;};
    std::uint32_t Colour;
} *PARGB;

typedef union ABGR
{
    struct {std::uint8_t A, B, G, R;};
    std::uint32_t Colour;
} *PABGR;

typedef struct
{
    float X, Y, Z, RHW;
    unsigned int Colour;
    float U, V;
} D3DVertex;

class StateBlock
{
private:
    IDirect3DStateBlock9* blk;

public:
    StateBlock(IDirect3DDevice9* pDevice, D3DSTATEBLOCKTYPE type = D3DSBT_ALL) : blk(nullptr) {pDevice->CreateStateBlock(type, &blk); blk->Capture();}
    StateBlock(const StateBlock& other) = delete;
    StateBlock(StateBlock&& other) : blk(other.blk) {other.blk = nullptr;}
    ~StateBlock() {blk->Apply(); blk->Release();}

    inline IDirect3DStateBlock9* operator()() const {return blk;}
};

//#ifdef D3DX_SUPPORT
#include <d3dx9.h>
class Font
{
private:
    ID3DXFont* fnt;
    int width, height;

public:
    Font(IDirect3DDevice9* pDevice, const char* name, unsigned short size);
    Font(const Font& other) = delete;
    Font(Font&& other) : fnt(other.fnt) {other.fnt = nullptr;}
    ~Font() {if(fnt) fnt->Release();}

    inline ID3DXFont* operator()() const {return fnt;}
    inline void OnLostDevice() {if(fnt) fnt->OnLostDevice();}
    inline void OnResetDevice() {if(fnt) fnt->OnResetDevice();}

    template<typename... Args>
    void Draw(float X, float Y, const char* Text, Args... args);

    template<typename... Args>
    void Draw(float X, float Y, const D3DCOLOR colour, const char* Text, Args... args);
};

template<typename... Args>
void Font::Draw(float X, float Y, const char* Text, Args... args)
{
    Draw(X, Y, 0xFFFFFFFF, Text, std::forward<Args>(args)...);
}

template<typename... Args>
void Font::Draw(float X, float Y, const D3DCOLOR colour, const char* Text, Args... args)
{
    std::size_t Position = 0;
    std::string Container(Text);
    std::vector<std::string> Arguments;
    std::initializer_list<int> {(Arguments.push_back(std::to_string(args)), 0)...};

    for (auto it = Arguments.begin(); it != Arguments.end(); ++it)
    {
        if ((Position = Container.find("%")) != std::string::npos)
        {
            Container.replace(Position, 1, *it);
        }
    }

    RECT rect = {(long)X, (long)Y, width, height};
	SetRect(&rect, X, Y, X + 500, Y + 20);
	fnt->DrawTextA(NULL, Container.c_str(), -1, &rect, DT_LEFT | DT_VCENTER, colour);
}
//#endif

class Image
{
private:
    void* pixels;
    unsigned int width, height;
    void process_pixels(void* out, void* in);
    void unprocess_pixels(void* out, void* in);

public:
    Image() : pixels(nullptr), width(0), height(0) {}
    Image(void* pixels, unsigned int width, unsigned int height);
    ~Image() {free(pixels); pixels = nullptr;}

    Image(const Image &other) = delete;
    Image(Image &&other) = delete;
    Image& operator = (const Image &other) = delete;

    bool Save(const char* path);
};

class Texture
{
private:
    IDirect3DTexture9* tex;
    IDirect3DDevice9* pDevice;

public:
    #ifdef D3DX_SUPPORT
    Texture(IDirect3DDevice9* pDevice, const char* path, const D3DCOLOR colourkey = 0xFF000000);
    #endif
    Texture(IDirect3DDevice9* pDevice, int width, int height, const D3DFORMAT format = D3DFMT_A8R8G8B8);
    Texture(const Texture& other) = delete;
    Texture(Texture&& other) : tex(other.tex), pDevice(other.pDevice) {other.tex = nullptr; other.pDevice = nullptr;}
    ~Texture() {if(tex) tex->Release();}

    inline IDirect3DTexture9* operator()() const {return tex;}
    std::uint8_t* Lock();
    void Unlock();
    void GetDescription(D3DSURFACE_DESC* desc);

    void Draw(float X1, float Y1, float X2, float Y2);
};

#ifdef D3DX_SUPPORT
class Sprite
{
private:
    ID3DXSprite* spr;
    IDirect3DDevice9* pDevice;

public:
    Sprite(IDirect3DDevice9* pDevice);
    Sprite(const Sprite& other) = delete;
    Sprite(Sprite&& other) : spr(other.spr), pDevice(other.pDevice) {other.spr = nullptr; other.pDevice = nullptr;}
    ~Sprite() {if(spr) spr->Release();}

    inline ID3DXSprite* operator()() const {return spr;}
    inline void OnLostDevice() {if(spr) spr->OnLostDevice();}
    inline void OnResetDevice() {if(spr) spr->OnResetDevice();}

    void Draw(IDirect3DTexture9* tex, D3DXVECTOR3* pos = nullptr, const D3DCOLOR tint = 0xFFFFFFFF);
};
#endif

class Graphics
{
private:
    IDirect3DDevice9* pDevice;

public:
    Graphics(IDirect3DDevice9* pDevice) : pDevice(pDevice) {}
    ~Graphics() {}

    void DrawCircle(float X, float Y, float Radius, D3DCOLOR Colour, int Resolution = 10);
};

#endif // GRAPHICS_HXX_INCLUDED
