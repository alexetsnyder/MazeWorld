#include "wall.h"

Wall::Wall(GLfloat width, GLfloat height, glm::vec3 position, dir facing)
{
	model = glm::mat4();
	model = glm::translate(model, position);

	if (facing == dir::NORTH || facing == dir::SOUTH)
	{
		model = glm::scale(model, glm::vec3(width, height, 1.0f));
	}
	else
	{
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, height, width));
	}

	display = true;

	cube = Cube::get_instance();
}

Wall::Wall()
{
	//Do Nothing
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