#ifndef CUBE_CLASS
#define CUBE_CLASS

#include <string>

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

class Cube
{
	public:
		static Cube* cube;
		static bool instance;
		static Cube* get_instance();

		Cube();
		~Cube();

		void draw();
		GLuint get_vao() { return VAO; }

	private:
		GLuint VAO;
		GLuint VBO;
		GLuint VEO;
};

#endif
