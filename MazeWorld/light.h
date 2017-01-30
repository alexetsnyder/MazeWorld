#ifndef LIGHT_BASE_CLASS
#define LIGHT_BASE_CLASS

//OpenGL Math Library GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
	public:
		Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

		glm::vec3& ambient() { return _ambient;  }
		glm::vec3& diffuse() { return _diffuse; }
		glm::vec3& specular() { return _specular; }
			
	private:
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
};

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


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
