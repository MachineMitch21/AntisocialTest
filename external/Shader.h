
#ifndef __SHADER_H__
#define __SHADER_H__

#include "AntisocialDLL.h"

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <GL/glew.h>

#define ERR_LOG 512

namespace antisocial {

	class
	#ifdef __WIN32__
	ANTISOCIAL_API
	#endif // __WIN32__
	Shader
	{
	public:
		Shader();
		Shader(const std::string& vert, const std::string& frag);
		~Shader();

		void bind();
		void unbind();

		GLuint& getProgram();

		void submitShaderFile(const std::string& file, GLenum type);

		//Only to be called if every shader type needed for the shader
		//program has been given to the shader object
		bool linkProgram();

		void setMatrix4(const std::string& name, const float* v);
		void setVector2(const std::string& name, float v1, float v2);
		void setVector3(const std::string& name, float v1, float v2, float v3);
		void setVector4(const std::string& name, float v1, float v2, float v3, float v4);
		void setFloat(const std::string& name, float v);
		void setBool(const std::string& name, bool v);
		void setInteger(const std::string& name, int v);
		void setUInteger(const std::string& name, unsigned int v);

	private:
		void init_shader_map();
		GLuint compile_shader(const std::string& shader_src, GLenum shader_type);
		std::string load_shader(const std::string& filename);

	private:
		GLint 						_success;
 		std::map<GLenum, GLuint> 	_shaders;
		GLuint 						_handle;
		GLchar 						_errLog[ERR_LOG];
	};

}

#endif // __SHADER_H__
