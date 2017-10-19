
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "AntisocialDLL.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <stdio.h>

namespace antisocial
{
    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    ModelLoader
    {
    public:

        static bool loadObj(const std::string& path,
                            std::vector<glm::vec3>& out_vertices,
                            std::vector<glm::vec3>& out_normals,
                            std::vector<glm::vec2>& out_uvs);
    private:
        ModelLoader();
        ~ModelLoader();
    };
}

#endif // MODELLOADER_H
