#ifndef SHADER_LOADER
#define SHADER_LOADER

#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
	public:
		Shader(std::string vshader, std::string fshader);
		Shader(std::string vshader, std::string gshader, std::string fshader);

		void use() { glUseProgram(_program); }
		GLuint program() { return _program; }

	private:
		GLuint _program;
};

std::string read_file(std::string file_name);

#endif

