#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
	: direction(DIRECTION), speed(SPEED), sensitivity(SENSITIVITY), _zoom(ZOOM)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + direction, up);
}

void Camera::moveCamera(camera_movement dir, GLfloat deltaTime)
{
	GLfloat velocity = speed * deltaTime;
	if (dir == FORWARD)
		position += direction * velocity;
	if (dir == BACKWARD)
		position -= direction * velocity;
	if (dir == LEFT)
		position -= right * velocity;
	if (dir == RIGHT)
		position += right * velocity;
}

void Camera::rotateCamera(GLfloat xoff, GLfloat yoff)
{
	xoff *= sensitivity;
	yoff *= sensitivity;

	yaw += xoff;
	pitch += yoff;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateVectors();
}

void Camera::zoomCamera(GLfloat yoff)
{
	if (_zoom >= 1.0f && _zoom <= 45.0f)
		_zoom -= yoff;
	if (_zoom <= 1.0f)
		_zoom = 1.0f;
	if (_zoom >= 45.0f)
		_zoom = 45.0f;
}

void Camera::updateVectors()
{
	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(dir);

	right = glm::normalize(glm::cross(direction, worldUp));
	up = glm::normalize(glm::cross(right, direction));
}