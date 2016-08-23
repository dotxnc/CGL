
#include "image.h"

void cgl_InitImage(Image* image, const char* path, float x, float y, float z)
{
	GLfloat vertices[] = {
		// Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	float texcoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		0.5, 1.0
	};
	
	image->x = x;
	image->y = y;
	image->z = z;
	
	image->rx = ((float)rand() / (float)RAND_MAX)*180;
	image->ry = ((float)rand() / (float)RAND_MAX)*180;
	image->rz = ((float)rand() / (float)RAND_MAX)*180;
	image->scale = (float)rand() / (float)RAND_MAX;

	glGenVertexArrays(1, &image->VAO);
	glGenBuffers(1, &image->VBO);

	glBindVertexArray(image->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// load diffuse map
	glGenTextures(1, &image->diffuseMap);
	glBindTexture(GL_TEXTURE_2D, image->diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image->image = SOIL_load_image("data/container.jpg", &image->width, &image->height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image->image);
	
	// load spec map
	glGenTextures(1, &image->specularMap);
	glBindTexture(GL_TEXTURE_2D, image->specularMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image->image = SOIL_load_image("data/SpecularMap.png", &image->width, &image->height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image->image);
	
	
}

void cgl_DrawImage(Image* image, ShaderProgram* prog, Camera* cam)
{

	cgl_UseProgram(prog);

	mat4x4 model;
	mat4x4_identity(model);
	mat4x4_translate(model, image->x, image->y, image->z);
	mat4x4_rotate(model, model, 1.0, 0.0, 0.0, -image->rx * (M_PI/ 180.0 ));
	mat4x4_rotate(model, model, 0.0, 1.0, 0.0, -image->ry * (M_PI/ 180.0 ));
	mat4x4_rotate(model, model, 0.0, 0.0, 1.0, -image->rz * (M_PI/ 180.0 ));
	mat4x4 view;
	mat4x4_identity(view);
	vec3 front;
	vec3_add(front, cam->pos, cam->front);
	mat4x4_look_at(view, cam->pos, front, cam->up);
	mat4x4 projection;
	mat4x4_identity(projection);
	mat4x4_perspective(projection, 45.0, cam->aspect, 0.01, 100.0);

	GLint modelLoc = glGetUniformLocation(prog->program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (*model));
	GLint viewLoc = glGetUniformLocation(prog->program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (*view));
	GLint projLoc = glGetUniformLocation(prog->program, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, (*projection));
	
	glUniform3f(glGetUniformLocation(prog->program, "light.position"), sin(glfwGetTime())*5, 0, -5+cos(glfwGetTime())*10);
	glUniform3f(glGetUniformLocation(prog->program, "viewPos"), cam->pos[0], cam->pos[1], cam->pos[2]);
	
	glUniform3f(glGetUniformLocation(prog->program, "lightColor"), 1.0, 0.5, 0.31);
	glUniform3f(glGetUniformLocation(prog->program, "objectColor"), 1.0, 1.0, 1.0);
	
	/// Material vars
	GLint matShineLoc = glGetUniformLocation(prog->program, "material.shininess"); 
	glUniform1f(matShineLoc, 32.0f);
	glUniform1i(glGetUniformLocation(prog->program, "material.diffuse"),  0);
	glUniform1i(glGetUniformLocation(prog->program, "material.specular"), 1);
	
	/// Light vars
	glUniform1f(glGetUniformLocation(prog->program, "light.linear"), 1.0);
	glUniform1f(glGetUniformLocation(prog->program, "light.constant"), 0.014);
	glUniform1f(glGetUniformLocation(prog->program, "light.quadratic"), 0.0007);
	glUniform3f(glGetUniformLocation(prog->program, "light.color"), 1.0, 0.2, 0.2);
	
	/// changing colors
	glUniform3f(glGetUniformLocation(prog->program, "light.ambient"),  0.f, 0.f, 0.f);
    glUniform3f(glGetUniformLocation(prog->program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(prog->program, "light.specular"), 1.0f, 1.f, 1.f);

	// DRAWING
	glUniform1i(glGetUniformLocation(prog->program, "material.diffuse"), 0);

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, image->diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, image->specularMap);
	
	glBindVertexArray(image->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, image->VBO);
	// position attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
	// normal attr
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
	// texcoord attr
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

}
