#include "Mesh.h"

std::vector<GLfloat> Mesh::pv;
std::vector<GLfloat> Mesh::pc;
std::vector<GLfloat> Mesh::pn;
std::vector<GLfloat> Mesh::pt;
std::vector<GLfloat> Mesh::pm;

void Mesh::Render(glm::mat4 const projection, glm::mat4 const view, ShaderProgram* shader)
{
	shader->Enable();

	glBindTexture(GL_TEXTURE_2D, 3);
	glUniform1i(shader->Uniform("tex0"), 0);

	glUniformMatrix4fv(shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	
	int szElements = Mesh::pv.size() + Mesh::pc.size() + Mesh::pn.size() + Mesh::pt.size() + Mesh::pm.size();

	int sz = 0;
	sz += Mesh::pv.size()*sizeof(glm::vec3);
	sz += Mesh::pc.size()*sizeof(glm::vec3);
	sz += Mesh::pn.size()*sizeof(glm::vec3);
	sz += Mesh::pt.size()*sizeof(glm::vec2);
	//sz += Mesh::pm.size()*sizeof(glm::mat4);

	struct b_data{
	public:
		std::vector<GLfloat> _v;
		std::vector<GLfloat> _c;
		std::vector<GLfloat> _n;
		std::vector<GLfloat> _t;
		//std::vector<GLfloat> _m;
	};

	typedef b_data BData;

	b_data buffer;
	buffer._v = Mesh::pv;
	buffer._c = pc;
	buffer._n = pn;
	buffer._t = pt;
	//buffer._m = pm;

	//std::vector<GLfloat> buffer;
	//buffer.resize(szElements);
	//buffer.insert(buffer.end(), Mesh::pv.begin(), Mesh::pv.end());
	//buffer.insert(buffer.end(), Mesh::pc.begin(), Mesh::pc.end());
	//buffer.insert(buffer.end(), Mesh::pn.begin(), Mesh::pn.end());
	//buffer.insert(buffer.end(), Mesh::pt.begin(), Mesh::pt.end());
	//buffer.insert(buffer.end(), Mesh::pm.begin(), Mesh::pm.end());



	glEnableVertexAttribArray(position);
	glEnableVertexAttribArray(color);
	glEnableVertexAttribArray(normal);
	glEnableVertexAttribArray(uv);
	glEnableVertexAttribArray(model);
	glEnableVertexAttribArray(model+1);
	glEnableVertexAttribArray(model+2);
	glEnableVertexAttribArray(model+3);

	GLuint vbo = -1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), &(buffer), GL_STATIC_DRAW);

	glVertexAttribPointer(
		position,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// offset
	);

	glVertexAttribPointer(
		color,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(Mesh::pv.size()*sizeof(glm::vec3))	// offset
	);

	glVertexAttribPointer(
		normal,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3))	// offset
	);

	glVertexAttribPointer(
		uv,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3)+Mesh::pn.size()*sizeof(glm::vec3))	// offset
	);

	//glVertexAttribPointer(
	//	model,   // the location in shader
	//	4,			// number of elements vec_3_
	//	GL_FLOAT,	// type of data
	//	GL_FALSE,	// normalized?
	//	sizeof(GLfloat) * 4 * 4,			// stride
	//	(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3)+Mesh::pn.size()*sizeof(glm::vec3)+Mesh::pt.size()*sizeof(glm::vec2))	// offset
	//);

	//glVertexAttribPointer(
	//	model+1,   
	//	4,			
	//	GL_FLOAT,	
	//	GL_FALSE,	
	//	sizeof(GLfloat) * 4 * 4,			
	//	(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3)+Mesh::pn.size()*sizeof(glm::vec3)+Mesh::pt.size()*sizeof(glm::vec2)+(sizeof(GLfloat) * 4))	
	//);

	//glVertexAttribPointer(
	//	model+2,  
	//	4,			
	//	GL_FLOAT,
	//	GL_FALSE,
	//	sizeof(GLfloat) * 4 * 4,			
	//	(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3)+Mesh::pn.size()*sizeof(glm::vec3)+Mesh::pt.size()*sizeof(glm::vec2)+(sizeof(GLfloat) * 8))	
	//);

	//glVertexAttribPointer(
	//	model+3,   
	//	4,			
	//	GL_FLOAT,	
	//	GL_FALSE,	
	//	sizeof(GLfloat) * 4 * 4,			
	//	(void*)(Mesh::pv.size()*sizeof(glm::vec3)+Mesh::pc.size()*sizeof(glm::vec3)+Mesh::pn.size()*sizeof(glm::vec3)+Mesh::pt.size()*sizeof(glm::vec2)+(sizeof(GLfloat) * 12))	
	//);

	glDrawArrays(GL_TRIANGLES, 0,  static_cast<GLsizei>(Mesh::pv.size()));

	// just send position and rotation;

	glDisableVertexAttribArray(position);
	glDisableVertexAttribArray(color);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(uv);
	glDisableVertexAttribArray(model);
	glDisableVertexAttribArray(model+1);
	glDisableVertexAttribArray(model+2);
	glDisableVertexAttribArray(model+3);
}

Mesh::Mesh(void)
{
	transform = glm::mat4(1.0);
	renderMethod = GL_TRIANGLES;

	shader = ShaderProgram::shaders["main"];
}

Mesh::~Mesh(void)
{

}

void Mesh::PrepareRender()
{
	if(e.size() > 0)
	{
		for(auto ik = e.begin(); ik != e.end(); ++ik)
		{
			GLubyte i = *ik;
			Mesh::pv.push_back(v[i].x); Mesh::pv.push_back(v[i].y); Mesh::pv.push_back(v[i].z);
			Mesh::pc.push_back(c[i].x); Mesh::pc.push_back(c[i].y); Mesh::pc.push_back(c[i].z);
			Mesh::pn.push_back(n[i].x); Mesh::pc.push_back(n[i].y); Mesh::pc.push_back(n[i].z);
			Mesh::pt.push_back(t[i].x); Mesh::pt.push_back(t[i].y);

			for(int j = 0; j < 4; ++j)
			{
				Mesh::pm.push_back(transform[j][0]);
				Mesh::pm.push_back(transform[j][1]);
				Mesh::pm.push_back(transform[j][2]);
				Mesh::pm.push_back(transform[j][3]);
			}
		}
	}
	else
	{

	}
}

void Mesh::Render(glm::mat4 projection, glm::mat4 view, glm::vec3 const lightDir)
{
	shader->Enable();

	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(shader->Uniform("tex0"), 0);

	glUniformMatrix4fv(shader->Uniform("model"), 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(shader->Uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(shader->Uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	

	//glUniform3fv(shader->Uniform("dirLight0"), 1, glm::value_ptr(lightDir));

	glEnableVertexAttribArray(position);
	glEnableVertexAttribArray(color);
	glEnableVertexAttribArray(normal);
	glEnableVertexAttribArray(uv);
	glEnableVertexAttribArray(model);

	// get total size of buffer
	int sz = sizeof(glm::vec3)*v.size();
	sz += sizeof(glm::vec3)*c.size();
	sz += sizeof(glm::vec3)*n.size();
	sz += sizeof(glm::vec2)*t.size();

	std::vector<float> buffer;
	
	for(auto i = v.begin(); i != v.end(); ++i)
		buffer.push_back((*i).x), buffer.push_back((*i).y), buffer.push_back((*i).z);

	for(auto i = c.begin(); i != c.end(); ++i)
		buffer.push_back((*i).x), buffer.push_back((*i).y), buffer.push_back((*i).z);

	for(auto i = n.begin(); i != n.end(); ++i)
		buffer.push_back((*i).x), buffer.push_back((*i).y), buffer.push_back((*i).z);

	for(auto i = t.begin(); i != t.end(); ++i)
		buffer.push_back((*i).x), buffer.push_back((*i).y);

	// vertices
	GLuint vbo = -1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*buffer.size(), &(buffer[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		position,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// offset
	);

	// colors
	//GLuint vco = -1;
	//glGenBuffers(1, &vco);
	//glBindBuffer(GL_ARRAY_BUFFER, vco);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*c.size(), &(c[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		color,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(sizeof(glm::vec3)*v.size())	// offset
	);

	// surface normals
	//GLuint vno = -1;
	//glGenBuffers(1, &vno);
	//glBindBuffer(GL_ARRAY_BUFFER, vno);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*n.size(), &(n[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		normal,   // the location in shader
		3,			// number of elements vec_3_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(sizeof(glm::vec3)*v.size()+sizeof(glm::vec3)*c.size())	// offset
	);

	// texture coords
	//GLuint vto = -1;
	//glGenBuffers(1, &vto);
	//glBindBuffer(GL_ARRAY_BUFFER, vto);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*t.size(), &(t[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(
		uv,   // the location in shader
		2,			// number of elements vec_2_
		GL_FLOAT,	// type of data
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)(sizeof(glm::vec3)*v.size()+sizeof(glm::vec3)*c.size()+sizeof(glm::vec3)*n.size())	// offset
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
	glDisableVertexAttribArray(uv);
	glDisableVertexAttribArray(model);
}