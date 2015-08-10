#ifndef MATH_HXX_INCLUDED
#define MATH_HXX_INCLUDED

#include <cmath>
#include <cstdint>
#include <algorithm>
#include <d3dx9.h>

class Mat4;

struct Vec3
{
public:
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    inline Vec3 Cross(const Vec3 &v) const;
    inline float Dot(const Vec3 &v) const;
    inline Vec3 Normalise() const;
    inline int Magnitude() const;
    inline Vec3 Scale(const float val) const;

    inline Vec3 operator + (const Vec3 &v) const;
    inline Vec3 operator - (const Vec3 &v) const;
    inline Vec3 operator * (const float val) const;
    inline Vec3 operator / (const float val) const;

    Vec3 Transform(Mat4* mat) const;
    Vec3 Transform(const Mat4 &mat) const;
    Vec3 Project(D3DVIEWPORT9* viewport, Mat4* world, Mat4* view, Mat4* projection) const;
    Vec3 Project(const D3DVIEWPORT9 &viewport, const Mat4 &world, const Mat4 &view, const Mat4 &projection) const;
};

class Mat4
{
private:
    float mat[4][4];

public:
    Mat4() : mat{0} {}

    float* operator[](const int index) {return mat[index];}
    const float* operator[](const int index) const {return mat[index];}

    Mat4 operator * (const Mat4 &m) const;
    Mat4 operator + (const Mat4 &m) const;
    Mat4 operator - (const Mat4 &m) const;

    Mat4& Transpose();
    Mat4 Transpose() const;
    static Mat4 Identity();
    static Mat4 Orthagonal(float w, float h, float zNear, float zFar);
    static Mat4 Perspective(float w, float h, float zNear, float zFar);
    static Mat4 FieldOfView(float fov, float aspect, float zNear, float zFar);
    static Mat4 LookAt(const Vec3& Eye, const Vec3& At, const Vec3& Up);

    static Mat4 RotX(float rad);
    static Mat4 RotY(float rad);
    static Mat4 RotZ(float rad);
    static Mat4 Rot(float pitch, float yaw, float roll);

    static Mat4 Scale(float val);
    static Mat4 Scale(float x, float y, float z);
    static Mat4 Translate(float x, float y, float z);
};

namespace DXMath
{
    unsigned int CalculateStride(unsigned int FVF);
    unsigned int CalculateBitsPerPixel(D3DFORMAT format);

    #ifdef D3DX_SUPPORT
    D3DXVECTOR3 WorldToScreen(D3DXMATRIX* WorldViewProjection, D3DVIEWPORT9* ViewPort, const D3DXVECTOR3 &in = {0, 0, 0});
    D3DXVECTOR3 WorldToScreen2(D3DVIEWPORT9* ViewPort, D3DXMATRIX* World, D3DXMATRIX* View, D3DXMATRIX* Projection, const D3DXVECTOR3 &in = {0, 0, 0});
    #else
    Vec3 WorldToScreen(Mat4* WorldViewProjection, D3DVIEWPORT9* ViewPort, const Vec3 &in = {0, 0, 0});
    Vec3 WorldToScreen2(D3DVIEWPORT9* ViewPort, Mat4* World, Mat4* View, Mat4* Projection, const Vec3 &in = {0, 0, 0});
    #endif
}


namespace GVMath
{
    typedef struct {float X1, Y1, X2, Y2;} Box2D;
    typedef struct {float X1, Y1, Z1, X2, Y2, Z2;} Box3D;

    static const double PI = 3.1415926535897932384626433832795;
    Vec3 GetEulerAngles(float (&mat)[16], bool RowMajor);
    Vec3 GetEulerAngles(float (&mat)[4][4], bool RowMajor);

    float Distance(float (&a)[2], float (&b)[2]);
    float Distance(float (&a)[3], float (&b)[3]);
    Box2D BoundingBox(float* x, float* y, std::size_t size);
    Box3D BoundingBox(float* x, float* y, float* z);

    std::uint32_t ColourChecksum(const void* data, std::size_t width, std::size_t height);
    std::uint32_t FullColourChecksum(const void* data, std::size_t width, std::size_t height, std::size_t offset = 0);

    std::uint32_t Adler32(const std::uint8_t* data, std::size_t size);
    std::uint32_t CRC32(const void* Data, size_t Size, std::uint32_t InitialValue = 0xFFFFFFFF);
}

#endif // MATH_HXX_INCLUDED
