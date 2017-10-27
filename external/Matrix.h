#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "AntisocialDLL.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "MathUtils.h"

#include <vector>
#include <iostream>
#include <cmath>

namespace antisocial
{
    namespace math
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Matrix
        {
        public:
            //Constructors
            Matrix();

            Matrix(float d);
            Matrix(Vector4f col1, Vector4f col2, Vector4f col3, Vector4f col4);
            Matrix(float matVars[16]);
            Matrix( float Xx, float Yx, float Zx, float Tx,
                    float Xy, float Yy, float Zy, float Ty,
                    float Xz, float Yz, float Zz, float Tz,
                    float Ox, float Oy, float Oz, float Os);
            ~Matrix();

            // Puts all the columns into a contiguous array in row-major order
            float* valueOf();

            // Projection methods
            static Matrix perspective(float fov, float aspectRatio, float nearClip, float farClip);
            static Matrix orthographic(float left, float right, float bottom, float top, float nearClip, float farClip);
            static Matrix lookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up);

            // Transformation methods
            static Matrix translate(Matrix& m, const Vector3f& v1);
            static Matrix rotate(Matrix& m, const Vector3f& v1, float angle);
            static Matrix scale(Matrix& m, const Vector3f& v1);
            Matrix& transpose();

            //Operator overloads
            Matrix& operator*=(const Matrix& m2);
            Matrix operator*(const Matrix& m2);
            Matrix& operator+=(const Matrix& m2);
            Matrix operator+(const Matrix& m2);
            bool operator==(const Matrix& m2);

            friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
            {
                return os << "[ " << m.xp.x << " " << m.yp.x << " " << m.zp.x << " " << m.tp.x <<" ]\n"
                          << "[ " << m.xp.y << " " << m.yp.y << " " << m.zp.y << " " << m.tp.y <<" ]\n"
                          << "[ " << m.xp.z << " " << m.yp.z << " " << m.zp.z << " " << m.tp.z <<" ]\n"
                          << "[ " << m.xp.w << " " << m.yp.w << " " << m.zp.w << " " << m.tp.w <<" ]\n";
            }

        public:
            Vector4f xp;
            Vector4f yp;
            Vector4f zp;
            Vector4f tp;

        private:
            float _elements[16];
        };
    }
}

#endif
