#include "Texture.hpp"
#include "../../third_party/stb_image.h"

Texture::Texture(std::string path, TextureType type) : path(path), type(type) {
	// Generate image data
	glGenTextures(1, &ID);
	bindObject();
	createTexture(path);
}

void Texture::createTexture(std::string path) {
	unsigned char* data;
	bindObject();
	// Generate image data
	stbi_set_flip_vertically_on_load(true);
	std::cout << "\nLoading texture in path: " << path;
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (!data && path != "n/a") data = stbi_load((directory + path).c_str(), &width, &height, &nrChannels, 0);
	if (!data) std::cout << "\nFailed to load texture with path: " << path << std::endl;
	int format;
	switch (nrChannels) 
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_RGB;
	}
	// Apply the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}