#include "Model_C.hpp"
#include "../../third_party/stb_image.h"

void Model_C::loadModel(std::string path) {
	Assimp::Importer importer;
	std::cout << "\nLoading model from: " << path;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene 
		|| scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE 
		|| !scene->mRootNode) {
		std::cout << "\nUnable to load model! ERRORR::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = std::string(path).substr(0, std::string(path).find_last_of('/') + 1).c_str();
	processNode(scene->mRootNode, scene);
}

void Model_C::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) 
		meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
	for (unsigned int i = 0; i < node->mNumChildren; i++) 
		processNode(node->mChildren[i], scene);
}

std::shared_ptr<RenderComponent> Model_C::processMesh(aiMesh* mesh, const aiScene* scene) {
	// Process vertices
	std::vector<float> vertices(mesh->mNumVertices * 8);
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		vertices[(i * 8)] = (float) mesh->mVertices[i].x;
		vertices[(i * 8) + 1] = (float) mesh->mVertices[i].y;
		vertices[(i * 8) + 2] = (float) mesh->mVertices[i].z;
		vertices[(i * 8) + 3] = (mesh->mTextureCoords[0]) ? (float) mesh->mTextureCoords[0][i].x : 0.0f;
		vertices[(i * 8) + 4] = (mesh->mTextureCoords[0]) ? (float) mesh->mTextureCoords[0][i].y : 0.0f;
		vertices[(i * 8) + 5] = (float) mesh->mNormals[i].x;
		vertices[(i * 8) + 6] = (float) mesh->mNormals[i].y;
		vertices[(i * 8) + 7] = (float) mesh->mNormals[i].z;
	}
	// Process indices
	std::vector<unsigned int> indices(mesh->mNumFaces * 3);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		for (unsigned int x = 0; x < mesh->mFaces[i].mNumIndices; x++)
			indices[i * 3 + x] = mesh->mFaces[i].mIndices[x];
	}
	// Process textures
	std::vector<Texture> textures = {};
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE);
		std::vector<Texture> specular = loadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), diffuse.begin(), diffuse.end());
		textures.insert(textures.end(), specular.begin(), specular.end());
	}

	return std::make_shared<RenderComponent>(vertices, indices, textures);
}

std::vector<Texture> Model_C::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
	std::vector<Texture> textures = {};
	aiString str;
	Texture::TextureType textureType;
	switch (type) {
		case aiTextureType_DIFFUSE:
			textureType = Texture::DIFFUSE;
			break;
		case aiTextureType_SPECULAR:
			textureType = Texture::SPECULAR;
			break;
		default:
			textureType = Texture::SPECULAR;
	}
	// Create textures from material
	bool skip = false;
	// Load all textures
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		mat->GetTexture(type, i, &str);
		skip = false;
		// Check if texture has already been loaded
		for (int j = 0; j < loadedTextures.size(); j++) {
			if (loadedTextures[j].getPath() == (directory + str.C_Str())
				|| loadedTextures[j].getPath() == (std::string) str.C_Str())
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			Texture texture = Texture(str.C_Str(), textureType);
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}

	return textures;
}