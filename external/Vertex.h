
#ifndef VERTEX_H
#define VERTEX_H

#include "AntisocialDLL.h"

#include "Vector2f.h"
#include "Vector3f.h"

namespace antisocial
{
    namespace graphics
    {
        struct
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Vertex
        {
            Vector3f position;
            Vector3f normal;
            Vector2f texCoord;
        };
    }
}

#endif // VERTEX_H
