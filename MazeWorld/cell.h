#pragma once

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "wall.h"
#include "quad.h"

const GLfloat WALL_WIDTH = 10.0f;
const GLfloat WALL_HEIGHT = 10.0f;
const GLfloat FLOOR_DIMEN = 10.0f;

class Cell
{
	public:
		Cell(glm::vec3 position);

		void draw(Shader shader);

	private:
		glm::vec3 position;
		Quad* floor;
		glm::mat4 floor_model;
		Wall wall[4];
};