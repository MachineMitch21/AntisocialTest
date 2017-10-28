#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__

#include "AntisocialDLL.h"
#include "stb_image.h"

#include <string>
#include <GL/glew.h>

namespace antisocial
{
	namespace graphics
	{
		namespace texture2D
		{
			#define TEXTURE_MIN_FILTER 	GL_TEXTURE_MIN_FILTER
			#define TEXTURE_MAG_FILTER 	GL_TEXTURE_MAG_FILTER
			#define TEXTURE_WRAP_X 		GL_TEXTURE_WRAP_S
			#define TEXTURE_WRAP_Y 		GL_TEXTURE_WRAP_T

			enum MIN_FILTER
			{
				MIN_NEAREST		= GL_NEAREST,
				MIN_LINEAR		= GL_LINEAR,
				MIPMAP_NN		= GL_NEAREST_MIPMAP_NEAREST,
				MIPMAP_LL		= GL_LINEAR_MIPMAP_LINEAR,
				MIPMAP_NL		= GL_NEAREST_MIPMAP_LINEAR,
				MIPMAP_LN		= GL_LINEAR_MIPMAP_NEAREST
			};

			enum MAG_FILTER
			{
				MAG_NEAREST			= GL_NEAREST,
				MAG_LINEAR			= GL_LINEAR
			};

			enum WRAPPING
			{
				CLAMP			= GL_CLAMP_TO_EDGE,
				MIRROR			= GL_MIRRORED_REPEAT,
				REPEAT			= GL_REPEAT
			};

			class
			#ifdef __WIN32__
			ANTISOCIAL_API
			#endif // __WIN32__
			Texture2D
			{
			public:
				Texture2D(const std::string& texturePath);
				~Texture2D();

				void setMinFilter(MIN_FILTER filter);
				void setMagFilter(MAG_FILTER filter);
				void setWrappingX(WRAPPING wrap);
				void setWrappingY(WRAPPING wrap);
				void setParameter(GLenum name, GLenum param);

				const MIN_FILTER& 	getMinFilter() const;
				const MAG_FILTER& 	getMagFilter() const;
				const WRAPPING&		getWrappingX() const;
				const WRAPPING& 	getWrappingY() const;

				void bind(unsigned int unit);
				void setImage(const std::string& path, unsigned int unit);
				inline GLuint getHandle() const { return _handle; };

			private:
				unsigned char* 	_data;
				GLuint 			_handle;
				int 			_height;
				int 			_width;
				int				_numComponents;
				MIN_FILTER		_minFilter;
				MAG_FILTER		_magFilter;
				WRAPPING		_xWrapping;
				WRAPPING		_yWrapping;
			};
		}
	}
}

#endif // __TEXTURE2D_H__
