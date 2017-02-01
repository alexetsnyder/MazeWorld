#ifndef CAMERA_CLASS
#define CAMERA_CLASS

//GLEW
#define STATIC_GLEW
#include <GL/glew.h>

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Default Camera Values
const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 DIRECTION = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 10.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

enum camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
	public:
		Camera(glm::vec3 position = POSITION, glm::vec3 up = UP, GLfloat yaw = YAW, GLfloat pitch = PITCH);
		glm::mat4 getViewMatrix();
		void moveCamera(camera_movement dir, GLfloat deltaTime);
		void rotateCamera(GLfloat xoff, GLfloat yoff);
		void zoomCamera(GLfloat yoff);

		GLfloat zoom() { return _zoom; }
		glm::vec3 pos() { return position; }
		glm::vec3 dir() { return direction; }

	private:
		void updateVectors();

		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 worldUp;
		glm::vec3 up;
		glm::vec3 right;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat speed;
		GLfloat sensitivity;
		GLfloat _zoom;
		
};

#endif
