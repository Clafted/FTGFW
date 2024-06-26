#ifndef MODEL_C_H
#define MODEL_C_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <memory>
#include "Component.hpp"
#include "RenderComponent.hpp"

struct Model_C : public Component {
public:
	std::vector<std::shared_ptr<RenderComponent>> meshes;
	inline Model_C(std::string modelPath) {
		loadModel(modelPath);
	}

private:
	std::vector<Texture> loadedTextures;
	std::string directory;
	
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);

	/* Create a RenderComponent with a provided mesh originating from a scene.
	* 
	* @param mesh - a pointer to the mesh to process
	* @param scene - a pointer to the scene containing the mesh */
	std::shared_ptr<RenderComponent> processMesh(aiMesh * mesh, const aiScene * scene);

	/* Create a vector of Textures from the provided material.
	* 
	* @param mat - the material containing the textures
	* @param type - the type of the texture
	* @return a vector of the Textures contained in the material */
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

#endif