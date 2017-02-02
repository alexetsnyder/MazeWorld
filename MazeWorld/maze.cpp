#include <time.h>
#include <cstdlib>
#include "maze.h"

//-------------------------------------------------------------------------
//-WALL CLASS
//-------------------------------------------------------------------------
Wall::Wall(glm::vec3 position, dir facing, GLfloat width, GLfloat height)
{
	model = glm::mat4();
	model = glm::translate(model, position);

	if (facing == dir::NORTH || facing == dir::SOUTH)
		model = glm::scale(model, glm::vec3(width, height, THICKNESS));
	else
		model = glm::scale(model, glm::vec3(THICKNESS, height, width));

	display = true;

	cube = Cube::get_instance();

	_dir = facing;
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

//-------------------------------------------------------------------------
//-POLE CLASS
//-------------------------------------------------------------------------
Pole::Pole(glm::vec3 position)
{
	cube = Cube::get_instance();

	model = glm::mat4();
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(THICKNESS, WALL_HEIGHT, THICKNESS));
}

void Pole::draw(Shader shader)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.program(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	cube->draw();
}

//-------------------------------------------------------------------------
//-CELL CLASS
//-------------------------------------------------------------------------
Cell::Cell(glm::vec3 position)
{
	this->position = position;

	floor = Quad::get_instance();
	floor_model = glm::translate(floor_model, glm::vec3(position.x, position.y - 5.0f, position.z));
	floor_model = glm::rotate(floor_model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	floor_model = glm::scale(floor_model, glm::vec3(FLOOR_DIMEN, FLOOR_DIMEN, 1.0f));

	walls[0] = Wall(glm::vec3(position.x, position.y, position.z - 4.5f), dir::NORTH);
	walls[1] = Wall(glm::vec3(position.x + 4.5f, position.y, position.z), dir::EAST);
	walls[2] = Wall(glm::vec3(position.x, position.y, position.z + 4.5f), dir::SOUTH);
	walls[3] = Wall(glm::vec3(position.x - 4.5f, position.y, position.z), dir::WEST);

	poles[0] = Pole(glm::vec3(position.x + 4.5f, position.y, position.z - 4.5f));
	poles[1] = Pole(glm::vec3(position.x - 4.5f, position.y, position.z - 4.5f));
	poles[2] = Pole(glm::vec3(position.x + 4.5f, position.y, position.z + 4.5f));
	poles[3] = Pole(glm::vec3(position.x - 4.5f, position.y, position.z + 4.5f));
}

bool Cell::toggle_wall(dir wall)
{
	return walls[wall].toggle_wall();
}

bool Cell::is_wall_displayed(dir wall)
{
	return walls[wall].is_displayed();
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
		walls[i].draw(shader);
	}

	glUniform3f(glGetUniformLocation(shader.program(), "color"), 0.3f, 0.3f, 0.3f);
	for (int i = 0; i < 4; ++i)
	{
		poles[i].draw(shader);
	}
}


//-------------------------------------------------------------------------
//-MAZE CLASS
//-------------------------------------------------------------------------
Maze::Maze(int row_count, int cols_count)
{
	srand((unsigned int)time(NULL));

	int mid_row = row_count / 2;
	int mid_cols = cols_count / 2;

	for (int i = mid_row * 10; i > mid_row * -10; i-=10)
	{
		std::vector<Cell> column;
		for (int j = mid_cols * -10; j < mid_cols * 10; j+=10)
		{
			column.push_back(Cell(glm::vec3((GLfloat)j, 0.0f, (GLfloat)i)));
		}
		grid.push_back(column);
	}
}

void Maze::draw(Shader shader)
{
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			grid[i][j].draw(shader);
		}
	}
}

void Maze::initialize()
{
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			for (unsigned int k = dir::NORTH; k <= dir::WEST; ++k)
			{
				if (!grid[i][j].is_wall_displayed((dir)k))
				{
					grid[i][j].toggle_wall((dir)k);
				}
			}
		}
	}
}

void Maze::binary_tree_algorithm()
{
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			bool north_wall = (i + 1 < grid.size()) ? false : true;
			bool east_wall = (j + 1 < grid[i].size()) ? false : true;

			if (!east_wall && !north_wall)
			{
				int coin = rand() % 2;
				if (coin == 0)
				{
					grid[i][j].toggle_wall(dir::NORTH);
					grid[i + 1][j].toggle_wall(dir::SOUTH);
				}
				else
				{
					grid[i][j].toggle_wall(dir::EAST);
					grid[i][j + 1].toggle_wall(dir::WEST);
				}
			}
			else if (!east_wall)
			{
				grid[i][j].toggle_wall(dir::EAST);
				grid[i][j + 1].toggle_wall(dir::WEST);
			}
			else if (!north_wall)
			{
				grid[i][j].toggle_wall(dir::NORTH);
				grid[i + 1][j].toggle_wall(dir::SOUTH);
			}
		}
	}
}

void Maze::sidewinder_algorithm()
{
	using namespace std;

	vector<Point> run;
	for (unsigned int i = 0; i < grid.size(); ++i)
	{
		run.clear();

		for (unsigned int j = 0; j < grid[i].size(); ++j)
		{
			bool north_wall = (i + 1 < grid.size()) ? false : true;
			bool east_wall = (j + 1 < grid[i].size()) ? false : true;

			run.push_back(Point(i, j));

			if (!east_wall && !north_wall)
			{
				int coin = rand() % 2;
				if (coin == 0)
				{
					grid[i][j].toggle_wall(dir::EAST);
					grid[i][j + 1].toggle_wall(dir::WEST);
				}
				else
				{
					int choice = rand() % run.size();
					Point cell = run[choice];
					run.clear();

					grid[cell.x()][cell.y()].toggle_wall(dir::NORTH);
					grid[cell.x() + 1][cell.y()].toggle_wall(dir::SOUTH);
				}
			}
			else if (!east_wall)
			{
				grid[i][j].toggle_wall(dir::EAST);
				grid[i][j + 1].toggle_wall(dir::WEST);
			}
			else if (!north_wall)
			{
				int choice = rand() % run.size();
				Point cell = run[choice];
				run.clear();

				grid[cell.x()][cell.y()].toggle_wall(dir::NORTH);
				grid[cell.x() + 1][cell.y()].toggle_wall(dir::SOUTH);
			}
		}
	}

}
