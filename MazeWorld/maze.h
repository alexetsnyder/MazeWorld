#pragma once
#include <vector>

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "geometry.h"
#include "graph.h"

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

class Point
{
	public:
		Point(int x, int y) { _x = x; _y = y; }

		int& x() { return _x; }
		int& y() { return _y; }

	private:
		int _x, _y;
};

class Maze
{
	public:
		Maze(int row_count=ROW_COUNT, int cols_count=COLS_COUNT);

		void draw(Shader shader);

		void initialize();
		void merge_gg();
		void possible_dirs(int row, int col, std::vector<dir>& dirs);
		int dir_to_node(int prv_node, dir prv_dir);
		void node_to_grid(int node_num, int& row, int& col);
		int grid_to_node(int row, int col) 
			{ return row * cols_count + row + col; }

		void binary_tree_algorithm();
		void sidewinder_algorithm();
		void aldous_broder_algorithm();
		void wilsons_algorithm();

	private:
		std::vector<std::vector<Cell> > grid;
		int cols_count, row_count;
		Graph graph;	
};