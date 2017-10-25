#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "AntisocialDLL.h"
#include "ModelLoader.h"
#include "Mesh.h"
#include "Drawable.h"
#include "stb_image.h"
#include "Texture2D.h"

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <vector>

using antisocial::graphics::Mesh;
using antisocial::graphics::Drawable;
using antisocial::ModelLoader;
using antisocial::graphics::Texture2D;


namespace antisocial
{
    namespace graphics
    {
        #define CUBE_MAP_FRONT   GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        #define CUBE_MAP_BACK    GL_TEXTURE_CUBE_MAP_POSITIVE_Z
        #define CUBE_MAP_TOP     GL_TEXTURE_CUBE_MAP_POSITIVE_Y
        #define CUBE_MAP_BOTTOM  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
        #define CUBE_MAP_RIGHT   GL_TEXTURE_CUBE_MAP_POSITIVE_X
        #define CUBE_MAP_LEFT    GL_TEXTURE_CUBE_MAP_NEGATIVE_X

        #define CUBE_MAP    GL_TEXTURE_CUBE_MAP
        #define TEXTURE_2D  GL_TEXTURE_2D

        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Skybox : public Drawable
        {
        public:
            Skybox(std::string front, std::string back, std::string top, std::string bottom, std::string right, std::string left);
            Skybox(std::string singleTextureSky);
            ~Skybox();

            void draw() override;

        private:
            bool loadSideTexture(GLenum side, std::string file);

        private:
            Mesh*   _cubeMesh;
            GLuint  _skyboxTexture;
            GLenum  _textureType;
            GLuint  _textureUnit;
        };
    }
}

#endif // __SKYBOX_H__
