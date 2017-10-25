#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "AntisocialDLL.h"

namespace antisocial
{
    namespace graphics
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Drawable
        {
        public:

            virtual void draw() = 0;
            virtual ~Drawable(){};
        };
    }
}

#endif // DRAWABLE_H
