#pragma once

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "cube.h"

enum dir {NORTH, SOUTH, EAST, WEST};

const GLfloat WALL_WIDTH = 10.0f;
const GLfloat WALL_HEIGHT = 10.0f;

class Wall
{
	public:
		Wall(glm::vec3 position, dir facing = dir::NORTH, GLfloat width=WALL_WIDTH, GLfloat height=WALL_HEIGHT);

		bool toggle_wall();

		void draw(Shader shader);

	private:
		Cube* cube;
		glm::mat4 model;
		bool display;
};

Wall::Wall(glm::vec3 position, dir facing, GLfloat width, GLfloat height)
{
	model = glm::mat4();
	model = glm::translate(model, position);
	
	if (facing == dir::NORTH || facing == dir::SOUTH)
	{
		model = glm::scale(model, glm::vec3(width, height, 1.0f));
	}
	else
	{
		model = glm::rotate(model, glm::radians(22.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, height, width));
	}
		
	display = true;

	cube = Cube::get_instance();
}

bool Wall::toggle_wall()
{
	display = !display;

	return display;
}

void Wall::draw(Shader shader)
{
	if (display)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.program(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		cube->draw();
	}
}