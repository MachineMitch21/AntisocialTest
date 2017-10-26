
#ifndef VECTOR4F_H
#define VECTOR4F_H

#include "AntisocialDLL.h"
#include <math.h>
#include <iostream>
#include <string>

namespace antisocial
{
    namespace math
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Vector4f
        {
        public:
            Vector4f();
            Vector4f(float x, float y, float z, float w);
            ~Vector4f();

            float magnitude();
            float dot(const Vector4f& v);
            Vector4f add(const Vector4f& v);
            Vector4f subtract(const Vector4f& v);

            float operator*(const Vector4f& v);
            Vector4f operator+(const Vector4f& v);
            Vector4f operator-(const Vector4f& v);
            bool operator==(const Vector4f& v);
            Vector4f& operator+=(const Vector4f& v);

            friend std::ostream& operator<<(std::ostream& os, const Vector4f& v)
            {
                return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
            }

            std::string toString()
            {
                return std::string(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w));
            }

        public:
            float x, y, z, w;
        };
    }
}

#endif // VECTOR4F_H
