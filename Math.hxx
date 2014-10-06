#ifndef MATH_HXX_INCLUDED
#define MATH_HXX_INCLUDED

#include <cmath>
#include <cstdint>
#include <algorithm>

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


namespace GVMath
{
    static const double PI = 3.1415926535897932384626433832795;

    Vec3 GetEulerAngles(float mat[16], bool RowMajor);
    Vec3 GetEulerAngles(float mat[4][4], bool RowMajor);
    std::uint32_t CRC32(void* Data, size_t Size, std::uint32_t InitialValue = 0xFFFFFFFF);
}

#endif // MATH_HXX_INCLUDED
