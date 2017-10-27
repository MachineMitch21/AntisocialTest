
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
            Vector3f();
            Vector3f(float x, float y, float z);
            ~Vector3f();

            static Vector3f normalize(const Vector3f& v);
            static Vector3f cross(const Vector3f& v1, const Vector3f& v2);
            static Vector3f add(const Vector3f& v1, const Vector3f& v2);
            static Vector3f subtract(const Vector3f& v1, const Vector3f& v2);
            static float dot(const Vector3f& v1, const Vector3f& v2);

            float magnitude() const;
            Vector3f scale(float scalar);

            static Vector3f Lerp(Vector3f v1, Vector3f v2, float t);

            Vector3f operator*(float scalar);
            Vector3f& operator+=(const Vector3f& v);
            Vector3f operator-();

            friend Vector3f operator+ (const Vector3f& v1, const Vector3f& v2);
            friend Vector3f operator- (const Vector3f& v1, const Vector3f& v2);

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

        Vector3f operator+ (const Vector3f& v1, const Vector3f& v2);
        Vector3f operator- (const Vector3f& v1, const Vector3f& v2);
    }
}

#endif // VECTOR3F_H
