#pragma once

//GLEW Library Wrangler
#define GLEW_STATIC
#include <GL/glew.h>

//GLM Math Library
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define POSITION 0
#define NORMAL	 1
#define TEXTURE  2

class Quad
{
	public:
		static Quad* quad;
		static bool instance;
		static Quad* get_instance();

		Quad();
		~Quad();

		void draw();

	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
};