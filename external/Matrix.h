#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "AntisocialDLL.h"
#include "Vector4f.h"

namespace antisocial
{
    namespace math
    {
        class ANTISOCIAL_API Matrix
        {
        public:
            Matrix();
            Matrix(Vector4f col1, Vector4f col2, Vector4f col3, Vector4f col4);
            Matrix(float matVars[16]);
            Matrix( float Xx, float Yx, float Zx, float Tx,
                    float Xy, float Yy, float Zy, float Ty,
                    float Xz, float Yz, float Zz, float Tz,
                    float Ox, float Oy, float Oz, float Os);

            friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
            {
                return os << "[ " << m.xp.x << m.yp.x << m.zp.x << m.tp.x <<" ]\n";
            }
           Vector4f xp;
           Vector4f yp;
           Vector4f zp;
           Vector4f tp;


        };
    }
}

#endif
