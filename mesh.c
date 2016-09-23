#include "mesh.h"

#include <iostream>
#include <sstream>

using std::stringstream;
using std::string;

void cgl_InitMesh(Mesh* mesh, Vertex* vlist, GLuint* ilist, Texture* tlist, int nv, int ni, int nt)
{
	mesh->vertices = vlist;
	mesh->indices = ilist;
	mesh->textures = tlist;
	
	mesh->num_vertices = nv;
	mesh->num_indices = ni;
	mesh->num_textures = nt;
	
	_cgl_setupmesh(mesh);
}

void cgl_DrawMesh(Mesh* mesh, ShaderProgram* shader)
{
	cgl_UseProgram(shader);
	
	int diffuseNr = 1;
	int specularNr = 1;
	for (int i = 0; i < mesh->num_textures; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		// I'm going to be SUUPER lazy here and use c++ string functionality
		// TODO: convert to pure C and drop the c++ requirement
		stringstream ss;
		string number;
		string name = string(mesh->textures[i].type);
		if (name == "texture_diffuse")
			ss << diffuseNr++;
		else if (name == "texture_specular")
			ss << specularNr++;
		number = ss.str();
		glUniform1f(glGetUniformLocation(shader->program, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->num_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

static void _cgl_setupmesh(Mesh* mesh)
{
	glGenVertexArrays(1, &mesh->VAO);
	glGenBuffers(1, &mesh->VBO);
	glGenBuffers(1, &mesh->EBO);
	
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VAO);
	glBufferData(GL_ARRAY_BUFFER, mesh->num_vertices * sizeof(Vertex), &mesh->vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->num_indices * sizeof(GLuint), &mesh->indices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	
	glBindVertexArray(0);
	
}
