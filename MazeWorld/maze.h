#pragma once
#include <vector>

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "geometry.h"

enum dir { NORTH, EAST, SOUTH, WEST };

const GLfloat WALL_WIDTH = 8.0f;
const GLfloat WALL_HEIGHT = 10.0f;
const GLfloat FLOOR_DIMEN = 10.0f;
const GLfloat THICKNESS = 1.0f;
const int ROW_COUNT = 20;
const int COLS_COUNT = 20;

class Wall
{
	public:
		Wall(glm::vec3 position = glm::vec3(0.0f), dir facing = dir::NORTH,
			 GLfloat width=WALL_WIDTH, GLfloat height=WALL_HEIGHT);

		bool toggle_wall();
		dir direction() { return _dir; }
		bool is_displayed() { return display; }

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

		bool toggle_wall(dir wall);
		bool is_wall_displayed(dir wall);

		void draw(Shader shader);

	private:
		glm::vec3 position;

		Quad* floor;
		glm::mat4 floor_model;

		Wall walls[4];
		Pole poles[4];
};

class Maze
{
	public:
		Maze(int row_count=ROW_COUNT, int cols_count=COLS_COUNT);

		void draw(Shader shader);

		void initialize();
		void binary_tree_algorithm();
		void sidewinder_algorithm();

	private:
		std::vector<std::vector<Cell> > grid;

};

class Point
{
	public:
		Point(int x, int y) { _x = x; _y = y; }

		int& x() { return _x; }
		int& y() { return _y; }

	private:
		int _x, _y;
};
