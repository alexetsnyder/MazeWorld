#pragma once

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "geometry.h"

enum dir { NORTH, SOUTH, EAST, WEST };

const GLfloat WALL_WIDTH = 8.0f;
const GLfloat WALL_HEIGHT = 10.0f;
const GLfloat FLOOR_DIMEN = 10.0f;
const GLfloat THICKNESS = 1.0f;

class Wall
{
	public:
		Wall(glm::vec3 position = glm::vec3(0.0f), dir facing = dir::NORTH,
			 GLfloat width=WALL_WIDTH, GLfloat height=WALL_HEIGHT);

		bool toggle_wall();
		dir direction() { return _dir; }

		void draw(Shader shader);

	private:
		Cube* cube;
		glm::mat4 model;

		dir _dir;
		bool display;
};

class Pole
{
	public:
		Pole(glm::vec3 position = glm::vec3(0.0f));

		void draw(Shader shader);

	private:
		Cube* cube;
		glm::mat4 model;
};

class Cell
{
	public:
		Cell(glm::vec3 position);

		void draw(Shader shader);

	private:
		glm::vec3 position;

		Quad* floor;
		glm::mat4 floor_model;

		Wall walls[4];
		Pole poles[4];
};
