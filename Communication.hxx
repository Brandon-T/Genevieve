#ifndef COMMUNICATION_HXX_INCLUDED
#define COMMUNICATION_HXX_INCLUDED

#include "MemoryMap.hxx"

typedef struct
{
    char letter;
    std::uint32_t ID;
    std::uint32_t FID;
    std::uint32_t X, Y;
    float vertices[18];
} FontInfo;

typedef struct
{
    std::uint32_t ID;
    std::uint32_t FID;
    std::uint32_t X, Y;
    float vertices[18];
} TextureInfo;

typedef struct
{
    std::uint32_t ID;
    std::uint32_t X, Y;
    std::uint32_t VertexCount;
    std::uint32_t PrimitiveCount;
    std::uint32_t PrimitiveType;

    std::uint32_t IID;
    std::uint32_t IICount;

    float RealBase[3];
    float Matrix[16];
} ModelInfo;

class Communication
{
private:
    Event request;
    Event response;
    MemoryMap memorymap;

    static const std::uint32_t kDebug = 0;
    static const std::uint32_t kTexture = 1;
    static const std::uint32_t kModel = 2;

public:
    Communication(const char* requestname, const char* responsename, const char* mapname, std::size_t mapsize, std::ios_base::openmode mapmode = std::ios::in | std::ios::out);
    void ProcessRequests();
    void ProcessResponses();
};

#endif // COMMUNICATION_HXX_INCLUDED
