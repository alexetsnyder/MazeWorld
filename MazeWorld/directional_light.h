#ifndef LIGHT_DIR_CLASS
#define LIGHT_DIR_CLASS

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "light.h"

class DirectionalLight : public Light
{
	public:
		DirectionalLight(glm::vec3 direction = glm::vec3(0.0f),
						 glm::vec3 ambient = glm::vec3(0.2f),
						 glm::vec3 diffuse = glm::vec3(0.5f),
						 glm::vec3 specular = glm::vec3(1.0f));

		glm::vec3& direction() { return _direction; }

	private:
		glm::vec3 _direction;
};

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient,
	glm::vec3 diffuse, glm::vec3 specular)
	: Light(ambient, diffuse, specular)
{
	_direction = direction;
}

#endif
