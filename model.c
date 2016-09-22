#include "model.h"

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
    	return -1;
    }
    if (stream == NULL) {
    	return -1;
    }
    if (n == NULL) {
    	return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
    	return -1;
    }
    if (bufptr == NULL) {
    	bufptr = malloc(128);
    	if (bufptr == NULL) {
    		return -1;
    	}
    	size = 128;
    }
    p = bufptr;
    while(c != EOF) {
    	if ((p - bufptr) > (size - 1)) {
    		size = size + 128;
    		bufptr = realloc(bufptr, size);
    		if (bufptr == NULL) {
    			return -1;
    		}
    	}
    	*p++ = c;
    	if (c == '\n') {
    		break;
    	}
    	c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}


const char* get_file_data(size_t* len, const char* filename) {
	const char* data;
	
	FILE * fp;
    char * line = NULL;
    ssize_t read;
  
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
  
    while ((read = getline(&line, &len, fp)) != -1) {
    	printf("%s", line);
		sprintf(data, "%s%s", data, line);
    }
  
    fclose(fp);
    if (line)
    	free(line);
    return data;
}

void cgl_LoadModel(Model* model, const char* filename)
{
	size_t data_len=0;
	const char* buffer = get_file_data(&data_len, filename);
	printf("Loaded obj with %d vertices\n", model->obj.num_vertices);
	tinyobj_parse_obj(&model->obj, &model->shape, &model->num_shapes, &model->materials, &model->num_materials, buffer, data_len, TINYOBJ_FLAG_TRIANGULATE);
	
}
