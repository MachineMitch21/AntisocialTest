
#ifndef VECTOR3F_H
#define VECTOR3F_H

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
        Vector3f
        {
        public:
            Vector3f(float x, float y, float z);
            ~Vector3f();

            float magnitude();
            float dot(const Vector3f& v);
            Vector3f cross(const Vector3f& v);
            Vector3f add(const Vector3f& v);
            Vector3f subtract(const Vector3f& v);

            float operator*(const Vector3f& v);
            Vector3f operator+(const Vector3f& v);
            Vector3f operator-(const Vector3f& v);

            friend std::ostream& operator<<(std::ostream& os, const Vector3f& v)
            {
                return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
            }

            std::string toString()
            {
                return std::string(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
            }

        public:
            float x, y, z;
        };
    }
}

#endif // VECTOR3F_H
