#ifndef MESH_H
#define MESH_H

#include "AntisocialDLL.h"
#include "Drawable.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include <GL/glew.h>
#include <vector>
#include <map>

using antisocial::graphics::Drawable;
using antisocial::math::Vector2f;
using antisocial::math::Vector3f;

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
            Mesh(const std::vector<Vector3f> vertices, const std::vector<Vector3f> normals, const std::vector<Vector2f> uvs);
            virtual ~Mesh();

            void draw() override;

            void setVertices(const std::vector<Vector3f> newVertices);
            void setNormals(const std::vector<Vector3f> newNormals);
            void setUVs(const std::vector<Vector2f> newUVs);

            inline std::vector<Vector3f>& getVertices()    { return _vertices; }
            inline std::vector<Vector3f>& getNormals()     { return _normals; }
            inline std::vector<Vector2f>& getUVs()         { return _uvs; }

        private:
            void init_vbo_map();

        private:

            std::vector<Vector3f>          _vertices;
            std::vector<Vector3f>          _normals;
            std::vector<Vector2f>          _uvs;
            GLuint                          _vao;
            std::map<unsigned int, GLuint>  _vbos;
        };
    }
}

#endif // MESH_H
