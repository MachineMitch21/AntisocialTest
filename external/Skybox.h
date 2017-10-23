#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "AntisocialDLL.h"
#include "Mesh.h"
#include "Drawable.h"
#include "stb_image.h"
#include "ModelLoader.h"
#include "Skybox.h"

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <vector>

using antisocial::Mesh;
using antisocial::Drawable;
using antisocial::ModelLoader;

#define CUBE_MAP_FRONT   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
#define CUBE_MAP_BACK    GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#define CUBE_MAP_TOP     GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#define CUBE_MAP_BOTTOM  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define CUBE_MAP_RIGHT   GL_TEXTURE_CUBE_MAP_POSITIVE_X
#define CUBE_MAP_LEFT    GL_TEXTURE_CUBE_MAP_NEGATIVE_X

namespace antisocial
{

    class
    #ifdef __WIN32__
    ANTISOCIAL_API
    #endif // __WIN32__
    Skybox : public Drawable
    {
    public:
        Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left);
        ~Skybox();

        void draw() override;

    private:
        bool loadSideTexture(GLenum side, std::string file);

    private:
        std::vector<float> _skyboxVertices;
        GLuint _cubeMapHandle;
        GLuint _vao;
        GLuint _vbo;
        Mesh* _cubeMesh;
    };

}

#endif // __SKYBOX_H__
