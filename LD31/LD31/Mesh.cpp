#include "Mesh.h"


Mesh::Mesh(void)
{
	transform = glm::mat4(1.0);
	renderMethod = GL_TRIANGLES;

	shader = ShaderProgram::shaders["main"];
}


Mesh::~Mesh(void)
{

}

void Mesh::Render(glm::mat4 projection, glm::mat4 view, glm::vec3 const lightDir)
{
	shader->Enable();

	glUniformMatrix4fv(shader->Uniform("model"), 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//glUniform3fv(shader->Uniform("dirLight0"), 1, glm::value_ptr(lightDir));


	glEnableVertexAttribArray(position);
	glEnableVertexAttribArray(color);
	glEnableVertexAttribArray(normal);

	// vertices
	GLuint vbo = -1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*v.size(), &(v[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		position,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// offset
	);

	// colors
	GLuint vco = -1;
	glGenBuffers(1, &vco);
	glBindBuffer(GL_ARRAY_BUFFER, vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*c.size(), &(c[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		color,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// offset
	);

	// surface normals
	GLuint vno = -1;
	glGenBuffers(1, &vno);
	glBindBuffer(GL_ARRAY_BUFFER, vno);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*n.size(), &(n[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		normal,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// offset
	);

	if(e.size() > 0)
	{
		GLuint veo = -1;
		glGenBuffers(1, &veo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*e.size(), &(e[0]), GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(e.size()), GL_UNSIGNED_BYTE, 0);
	}
	else 
	{
		glDrawArrays(renderMethod, 0, static_cast<GLsizei>(v.size()));
	}

	glDisableVertexAttribArray(position);
	glDisableVertexAttribArray(color);
	glDisableVertexAttribArray(normal);
}