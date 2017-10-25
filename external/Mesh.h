#ifndef MESH_H
#define MESH_H

#include "AntisocialDLL.h"
#include "Drawable.h"
#include <GL/glew.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>

using antisocial::graphics::Drawable;

namespace antisocial
{
    namespace graphics
    {
        #define NUM_VBOS    3

        #define VERTICES    0
        #define NORMALS     1
        #define UVS         2

        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Mesh : public Drawable
        {
        public:
            Mesh();
            Mesh(const std::vector<glm::vec3> vertices, const std::vector<glm::vec3> normals, const std::vector<glm::vec2> uvs);
            virtual ~Mesh();

            void draw() override;

            void setVertices(const std::vector<glm::vec3> newVertices);
            void setNormals(const std::vector<glm::vec3> newNormals);
            void setUVs(const std::vector<glm::vec2> newUVs);

            inline std::vector<glm::vec3>& getVertices()    { return _vertices; }
            inline std::vector<glm::vec3>& getNormals()     { return _normals; }
            inline std::vector<glm::vec2>& getUVs()         { return _uvs; }

        private:
            void init_vbo_map();

        private:

            std::vector<glm::vec3>          _vertices;
            std::vector<glm::vec3>          _normals;
            std::vector<glm::vec2>          _uvs;
            GLuint                          _vao;
            std::map<unsigned int, GLuint>  _vbos;
        };
    }
}

#endif // MESH_H
