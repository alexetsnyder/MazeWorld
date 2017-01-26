#ifndef LIGHT_POINT_CLASS
#define LIGHT_POINT_CLASS

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "light.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 position = glm::vec3(0.0f),
			   float linear = 0.045f, 
			   float quadratic = 0.0075f, 
			   float constant = 1.0f,
			   glm::vec3 ambient = glm::vec3(0.2f),
			   glm::vec3 diffuse = glm::vec3(0.5f),
			   glm::vec3 specular = glm::vec3(1.0f));

	glm::vec3& position() { return _position; }
	float& constant() { return _constant; }
	float& linear() { return _linear; }
	float& quadratic() { return _quadratic; }

private:
	glm::vec3 _position;

	float _constant;
	float _linear;
	float _quadratic;
};

PointLight::PointLight(glm::vec3 position, float linear, float quadratic,
					   float constant, glm::vec3 ambient, glm::vec3 diffuse,
					   glm::vec3 specular)
	: Light(ambient, diffuse, specular)
{
	_position = position;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
}

#endif
