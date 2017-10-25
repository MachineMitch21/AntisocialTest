
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "AntisocialDLL.h"
#include "Vector2f.h"
#include "Drawable.h"

#include <GL/glew.h>

using antisocial::graphics::Drawable;
using antisocial::math::Vector2f;

namespace antisocial
{
    namespace graphics
    {
        class
        #ifdef __WIN32__
        ANTISOCIAL_API
        #endif // __WIN32__
        Sprite  :   public Drawable
        {
        public:
            Sprite(const Vector2f& pos, float width, float height);
            Sprite(float x, float y, float width, float height);
            ~Sprite();

            void draw() override;
            void setPosition(const Vector2f& pos);
            void setWidth(float width);
            void setHeight(float height);

        private:
            void init_();
            void setData_();
        private:
            Vector2f    _position;
            float       _width;
            float       _height;
            GLuint      _vbo;
            GLuint      _vao;
        };
    }
}

#endif // __SPRITE_H__
