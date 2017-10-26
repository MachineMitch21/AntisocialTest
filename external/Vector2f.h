
#ifndef VECTOR2F_H
#define VECTOR2F_H

#include "AntisocialDLL.h"

#include <iostream>
#include <math.h>
#include <string>

namespace antisocial
{
    namespace math
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Vector2f
        {
        public:
            Vector2f();
            Vector2f(float x, float y);
            ~Vector2f();

            float magnitude();
            float dot(const Vector2f& v);
            Vector2f add(const Vector2f& v);
            Vector2f subtract(const Vector2f& v);

            float operator*(const Vector2f& v);
            Vector2f operator+(const Vector2f& v);
            Vector2f operator-(const Vector2f& v);

            friend std::ostream& operator<<(std::ostream& os, const Vector2f& v)
            {
                return os << "(" << v.x << ", " << v.y << ")";
            }

            std::string toString()
            {
                return std::string(std::to_string(x) + ", " + std::to_string(y));
            }

        public:
            float x, y;
        };
    }
}

#endif // VECTOR2F_H
