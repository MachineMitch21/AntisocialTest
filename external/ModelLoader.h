
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "AntisocialDLL.h"
#include "Mesh.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using antisocial::Mesh;

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
