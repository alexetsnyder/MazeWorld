#include <iostream>
#include <cstdlib>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW Window Manager
#include <GLFW\glfw3.h>

//GLM Mathematics
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//My Libraries
#include "shader.h"
#include "camera.h"
#include "maze.h"

#define START_WIDTH  800
#define START_HEIGHT 600

//Global Variables
Camera camera(glm::vec3(0.0f, 15.0f, 3.0f));
Maze* maze;
GLfloat deltaTime = 0.0f, lastFrame = 0.0f;
int screenWidth = START_WIDTH, screenHeight = START_HEIGHT;
GLfloat lastX = START_WIDTH / 2, lastY = START_HEIGHT / 2;
bool firstMouse = true;
bool noCursor = true;
bool keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void size_callback(GLFWwindow* window, int width, int height);
void movement();

int main()
{
	using namespace std;

	//Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//glfwWindowHint(GLFW_SAMPLES, 4);

	//Create Window
	GLFWwindow* window = glfwCreateWindow(START_WIDTH, START_HEIGHT, "MazeWorld", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "ERROR: GLFW Window not Created.\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//Set Callback Functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetWindowSizeCallback(window, size_callback);

	//Options 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW could not be Initialized.\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Define OpenGL Viewport Dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	//OpenGL Options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	//Compile Shaders
	Shader shader("vshader.glsl", "fshader.glsl");
	
	maze = new Maze(6, 6);
	maze->binary_tree_algorithm();

	while (!glfwWindowShouldClose(window))
	{
		//Set Frame Time
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Check and Call Events
		glfwPollEvents();
		movement();

		//Clear the Color Buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Render Scene
		shader.use();

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

		//model = glm::mat4();
		view = camera.getViewMatrix();
		projection = glm::perspective(glm::radians(camera.zoom()), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 300.0f);

		//glUniformMatrix4fv(glGetUniformLocation(shader.program(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.program(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		maze->draw(shader);

		//Swap Buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		if (noCursor)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			noCursor = false;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			noCursor = true;
		}
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		maze->initialize();
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		maze->initialize();
		maze->binary_tree_algorithm();
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = (GLfloat)xPos;
		lastY = (GLfloat)yPos;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat)xPos - lastX;
	GLfloat yOffset = lastY - (GLfloat)yPos; //Invert Y-axis

	lastX = (GLfloat)xPos;
	lastY = (GLfloat)yPos;

	camera.rotateCamera(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.zoomCamera((GLfloat)yOffset);
}

void movement()
{
	if (keys[GLFW_KEY_W])
		camera.moveCamera(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.moveCamera(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.moveCamera(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.moveCamera(RIGHT, deltaTime);
}


void size_callback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	glViewport(0, 0, width, height);
}