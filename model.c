#include "model.h"

void cgl_LoadModel(Model* model, const char* filename)
{
	list_make(&model->meshes, 128, sizeof(Mesh), true);
	
	// load model
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		printf("Failed to load assimp node: %s\n", importer.GetErrorString());
		free(scene);
		return;
	}
	
	
	std::string path = std::string(filename);
	model->directory = path.substr(0, path.find_last_of('/')).c_str();
	_cgl_processnode(model, scene->mRootNode, scene);
}

void cgl_DrawModel(Model* model, ShaderProgram* shader, Camera* cam, float x, float y, float z)
{
	for (int i = 0; i < model->meshes.item_count; i++) {
		cgl_DrawMesh(((Mesh*)(list_get_index(&model->meshes, i))), shader);
	}
}

static void _cgl_processnode(Model* model, aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		list_add_item(&model->meshes, _cgl_processmesh(model, mesh, scene), NULL);
	}
	for (int i = 0; i < node->mNumChildren; i++) {
		_cgl_processnode(model, node->mChildren[i], scene);
	}
}

static Mesh* _cgl_processmesh(Model* model, aiMesh* mesh, const aiScene* scene)
{
	list _vertices;
	list _indices;
	list _textures;
	list_make(&_vertices, 128, sizeof(Vertex), true);
	list_make(&_vertices, 128, sizeof(GLuint), true);
	list_make(&_vertices, 128, sizeof(Texture), true);
	
	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		list_add_item(&_vertices, &vertex, NULL);
	}
	
	if (mesh->mMaterialIndex >= 0)
	{
		
	}
	
	Mesh* _mesh;
	cgl_InitMesh(_mesh, &_vertices, &_indices, &_textures, 0, 0, 0);
	
	return _mesh;
	
}

static list* _cgl_loadmaterialtextures(Model* model, aiMaterial* mat, aiTextureType type, char* name)
{
	
}
