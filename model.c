#include "model.h"

// const char* get_file_data(size_t* _len, const char* filename) {
// 	// char data[MAXBUFLEN+1];
// 	char* data = NULL;
// 	
// 	FILE* fp;
// 	fp = fopen(filename, "r");
// 	if (fp != NULL) {
// 		if (fseek(fp, 0L, SEEK_END) == 0) {
// 			long buffsize = ftell(fp);
// 			if (buffsize == -1) { return NULL; }
// 			
// 			data = malloc((buffsize+1) * sizeof(char));
// 			if (fseek(fp, 0L, SEEK_SET) != 0) { return NULL; }
// 			size_t len = fread(data, sizeof(char), buffsize, fp);
// 			if (ferror(fp) != 0) {
// 				printf("Error reading file %s\n", filename);
// 			} else {
// 				data[len++] = '\0';
// 			}
// 			*_len += len;
// 		}
// 	}
// 	fclose(fp);
// 	return data;
// }

void cgl_LoadModel(Model* model, const char* filename)
{
	
	// Generate opengl buffers
	// glGenVertexArrays(1, &model->VAO);
	// glGenBuffers(1, &model->VBO);
	// 
	// glBindVertexArray(model->VAO);
	// 
	// glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	// glBufferData(GL_ARRAY_BUFFER, model->data.vertex_count, model->data.vertex_list, GL_STATIC_DRAW);
	// 
	// glBindVertexArray(0);
	
	// TODO: Textures
	
}

void cgl_DrawModel(Model* model, ShaderProgram* shader, Camera* cam, float x, float y, float z)
{
	// cgl_UseProgram(shader);
	// 
	// mat4x4 tran;
	// mat4x4_identity(tran);
	// mat4x4_translate(tran, x, y, z);
	// // TODO: rotation
	// 
	// GLint modelLoc = glGetUniformLocation(shader->program, "model");
	// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (*tran));
	// 
	// GLint matShineLoc = glGetUniformLocation(shader->program, "matrerial.shininess");
	// glUniform1f(matShineLoc, 32.0f);
	// // TODO: textures
	// 
	// // Draw
	// glBindVertexArray(model->VAO);
	// glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	// // position attr
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	// glEnableVertexAttribArray(0);
	// 
	// glDrawArrays(GL_TRIANGLES, 0, model->data.vertex_count/3);
	// glBindVertexArray(0);
}
