#pragma once

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "cube.h"

enum dir {NORTH, SOUTH, EAST, WEST};

class Wall
{
	public:
		Wall();
		Wall(GLfloat width, GLfloat height, glm::vec3 position=glm::vec3(0.0f), dir facing = dir::NORTH);

		bool toggle_wall();

		void draw(Shader shader);

	private:
		Cube* cube;
		glm::mat4 model;
		bool display;
};
