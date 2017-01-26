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

#endif
