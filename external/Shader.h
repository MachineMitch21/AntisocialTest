
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
		/*
		Creates an empty program object and stores a handle to it
		in the _handle variable. If you do not pass in a vertex or fragment
		shader their values will be set to -1.
		*/
		Shader();
		//Loads shaders from file and sends them to newly created program object
		Shader(const std::string& vert, const std::string& frag);
		~Shader();

		//Tells GL to use the current _handle as shader program.
		void bind();
		//Tells GL to stop using currently binded shader program.
		void unbind();

		//Returns _handle variable containing a handle to current shader program
		GLuint& getProgram();
		//Loads and compiles shader files.
		void submitShaderFile(const std::string& file, GLenum type);

		/*
		Iterates through _shaders map and attatches all the shader objects
		to the shader program referenced by _handle. This should only be called
		if every shader type needed for the shader program has been provided.
		*/
		bool linkProgram();

		/*
		Setting uniform shader variables by type. Pass in the name of the
		varible you wish to change and the value it is to be changed to.
		*/
		void setMatrix4(const std::string& name, const float* v);
		void setVector2(const std::string& name, float v1, float v2);
		void setVector3(const std::string& name, float v1, float v2, float v3);
		void setVector4(const std::string& name, float v1, float v2, float v3, float v4);
		void setFloat(const std::string& name, float v);
		void setBool(const std::string& name, bool v);
		void setInteger(const std::string& name, int v);
		void setUInteger(const std::string& name, unsigned int v);

	private:
		//Initializes _shaders map
		void init_shader_map();

		/*
		Move provided source code into shader and compiles it.
		returns handle to shader object.
		*/
		GLuint compile_shader(const std::string& shader_src, GLenum shader_type);

		//Loads shader source code from file and returns it as a string.
		std::string load_shader(const std::string& filename);

	private:
		GLint 						_success;
 		std::map<GLenum, GLuint> 	_shaders;
		GLuint 						_handle;
		GLchar 						_errLog[ERR_LOG];
	};

}

#endif // __SHADER_H__
