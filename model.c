#include "model.h"

const char* get_file_data(size_t* _len, const char* filename) {
	// char data[MAXBUFLEN+1];
	char* data = NULL;
	
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp != NULL) {
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long buffsize = ftell(fp);
			if (buffsize == -1) { return NULL; }
			
			data = malloc((buffsize+1) * sizeof(char));
			if (fseek(fp, 0L, SEEK_SET) != 0) { return NULL; }
			size_t len = fread(data, sizeof(char), buffsize, fp);
			if (ferror(fp) != 0) {
				printf("Error reading file %s\n", filename);
			} else {
				data[len++] = '\0';
			}
			*_len += len;
		}
	}
	fclose(fp);
	return data;
}

void cgl_LoadModel(Model* model, const char* filename)
{
	model->shape = NULL;
	model->materials = NULL;
	
	size_t data_len=0;
	const char* buffer = get_file_data(&data_len, filename);
	printf("loaded obj data with length of %d\n", data_len);
	
	int ret = tinyobj_parse_obj(&model->obj, &model->shape, &model->num_shapes, &model->materials, &model->num_materials, buffer, data_len, TINYOBJ_FLAG_TRIANGULATE);
	if (ret != TINYOBJ_SUCCESS) {
		printf("error: %d\n", ret);
	}
	else {
		printf("loaded obj with %d vertices\n", model->obj.num_vertices);
	}
	
}
