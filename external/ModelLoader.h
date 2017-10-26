
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "AntisocialDLL.h"
#include "Mesh.h"
#include "Vector2f.h"
#include "Vector3f.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using antisocial::graphics::Mesh;

namespace antisocial
{
    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    ModelLoader
    {
    public:

        static Mesh* loadObj(const std::string& path);
    private:
        ModelLoader();
        ~ModelLoader();
    };
}

#endif // MODELLOADER_H
