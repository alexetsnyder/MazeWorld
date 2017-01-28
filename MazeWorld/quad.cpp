#include "quad.h"

bool Quad::instance = false;
Quad* Quad::quad;

Quad* Quad::get_instance()
{
	if (!instance)
		quad = new Quad();
	
	return quad;
}

Quad::Quad()
{
	if (!instance)
	{
		instance = true;

		GLfloat quadVerticies[] =
		{
			//Position		    //Normal		   //Texture
			 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f
		};

		GLuint quadIndicies[] =
		{
			2, 1, 0,
			2, 0, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerticies), quadVerticies, GL_STATIC_DRAW);

		glEnableVertexAttribArray(POSITION);
		glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 8 *sizeof(GLfloat), (GLvoid*)0);

		glEnableVertexAttribArray(NORMAL);
		glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));

		glEnableVertexAttribArray(TEXTURE);
		glVertexAttribPointer(TEXTURE, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndicies), quadIndicies, GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Quad::draw()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}