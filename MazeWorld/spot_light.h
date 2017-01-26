#ifndef LIGHT_SPOT_CLASS
#define LIGHT_SPOT_CLASS

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "point_light.h"

class SpotLight : public PointLight
{
public:
	SpotLight(glm::vec3 position = glm::vec3(0.0f),
			  glm::vec3 direction = glm::vec3(0.0f),
		      float inner = 25.0f, float outer = 35.0f,
		      float linear = 0.045f,
		      float quadratic = 0.0075f,
		      float constant = 1.0f,
			  glm::vec3 ambient = glm::vec3(0.2f),
			  glm::vec3 diffuse = glm::vec3(0.5f),
		      glm::vec3 specular = glm::vec3(1.0f));

	glm::vec3& direction() { return _direction; }
	float& inner() { return _inner; }
	float& outer() { return _outer; }

private:
	glm::vec3 _direction;
	float _inner;
	float _outer;
};

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float inner, 
	                 float outer, float linear, float quadratic, float constant,
					 glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	: PointLight(position, linear, quadratic, constant, ambient, diffuse, specular)
{
	_inner = inner;
	_outer = outer;
}

#endif
