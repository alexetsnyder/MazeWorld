#include "cell.h"

Cell::Cell(glm::vec3 position)
{
	this->position = position;

	floor = Quad::get_instance();
	floor_model = glm::translate(floor_model, glm::vec3(position.x, position.y - 5.0f, position.z));
	floor_model = glm::rotate(floor_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	floor_model = glm::scale(floor_model, glm::vec3(FLOOR_DIMEN, FLOOR_DIMEN, 1.0f));

	wall[0] = Wall(WALL_WIDTH, WALL_HEIGHT, glm::vec3(position.x, position.y, position.z + 4.5f), dir::NORTH);
	wall[1] = Wall(WALL_WIDTH, WALL_HEIGHT, glm::vec3(position.x + 4.5f, position.y, position.z), dir::EAST);
	wall[2] = Wall(WALL_WIDTH, WALL_HEIGHT, glm::vec3(position.x, position.y, position.z - 4.5f), dir::SOUTH);
	wall[3] = Wall(WALL_WIDTH, WALL_HEIGHT, glm::vec3(position.x - 4.5f, position.y, position.z), dir::WEST);
}

void Cell::draw(Shader shader)
{
	glUniform3f(glGetUniformLocation(shader.program(), "color"), 0.4f, 0.4f, 0.4f);
	glUniformMatrix4fv(glGetUniformLocation(shader.program(), "model"), 1, GL_FALSE, glm::value_ptr(floor_model));
	floor->draw();

	for (int i = 0; i < 4; ++i)
	{	
		glm::vec3 color;

		switch (i)
		{
			case 0:
				color = glm::vec3(1.0f, 0.0f, 0.0f);
				break;
			case 1:
				color = glm::vec3(0.0f, 1.0f, 0.0f);
				break;
			case 2:
				color = glm::vec3(0.0f, 0.0f, 1.0f);
				break;
			case 3:
				color = glm::vec3(1.0f, 1.0f, 0.0f);
				break;
		}

		glUniform3f(glGetUniformLocation(shader.program(), "color"), color.x, color.y, color.z);
		wall[i].draw(shader);
	}
}