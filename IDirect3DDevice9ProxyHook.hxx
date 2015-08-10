#ifndef IDIRECT3DDEVICE9PROXYHOOK_HXX_INCLUDED
#define IDIRECT3DDEVICE9PROXYHOOK_HXX_INCLUDED

#include "IDirect3DDevice9Proxy.hxx"
#include "IDirect3DTexture9Proxy.hxx"
#include "IDirect3DSwapChain9Proxy.hxx"
#include "IDirect3DIndexBuffer9Proxy.hxx"
#include "IDirect3DVertexBuffer9Proxy.hxx"

#include "Graphics.hxx"
#include "Math.hxx"
#include "Plugin.hxx"
#include "MemoryMap.hxx"
#include "Communication.hxx"

#include <memory>
#include <vector>

class IDirect3DDevice9ProxyHook : public IDirect3DDevice9Proxy
{
private:
    std::uint32_t references;

    std::unique_ptr<Font> font;
    IDirect3DTexture9Proxy* pTexture;
    IDirect3DIndexBuffer9Proxy* pIndexBuffer;
    IDirect3DVertexBuffer9Proxy* pVertexBuffer;

    #ifdef D3DX_SUPPORT
    D3DVIEWPORT9 ViewPort;
    D3DXMATRIX World, View, Projection;
    D3DXMATRIX WorldViewProjection;
    #else
    D3DVIEWPORT9 ViewPort;
    Mat4 World, View, Projection;
    Mat4 WorldViewProjection;
    #endif

protected:
    const std::uint32_t ImageSize         =  8294400;                //Highest Default Resolution Support: 1920 x 1080 x sizeof(RGBA)
    const std::uint32_t TotalImageSize    =  (ImageSize * 2);        //Image + DebugImage
    const std::uint32_t HookSize          =  5242880;                //Space to allocate for hooks. 5mb max.



    const char* MemName = "Local\\GenevieveImage_";
    const char* RequestEventName = "Local\\GenevieveEvent_Request";
    const char* ResponseEventName = "Local\\GenevieveEvent_Response";

    std::unique_ptr<MemoryMap> ImgMap;      //Image Map
    std::unique_ptr<Communication> CommMap;
    std::vector<TextureInfo> textures;
    std::vector<ModelInfo> models;

    void HandleMemory(bool AllocateImage);
    void HandleCommunication();
    void HandleDebugDrawing();



public:
    IDirect3DDevice9ProxyHook(IDirect3DDevice9* pOriginal);
    virtual ~IDirect3DDevice9ProxyHook();

    //Override references
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();



    //Override rendering
    HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
    HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
    HRESULT __stdcall BeginScene();
    HRESULT __stdcall EndScene();
    HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters);


    //Override creations
    HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain);
    HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
    HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle);
    HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle);


    //Override setters
    HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture);
    HRESULT __stdcall SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride);
    HRESULT __stdcall SetIndices(IDirect3DIndexBuffer9* pIndexData);


    //Override consumers
    HRESULT __stdcall GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain);
    HRESULT __stdcall ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags);
};
#endif // IDIRECT3DDEVICE9PROXYHOOK_HXX_INCLUDED
