
#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

#include "AntisocialDLL.h"

namespace antisocial
{
    namespace math
    {
        #define PI 3.14159265358979323846

        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        MathUtils
        {
        public:
            static float to_radians(float degrees)
            {
                return degrees * (PI / 180);
            }

        private:
            MathUtils();
            ~MathUtils();
        };
    }
}

#endif // __MATHUTILS_H__
