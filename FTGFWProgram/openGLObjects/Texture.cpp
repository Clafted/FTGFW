#include "Texture.hpp"
#include "../../third_party/stb_image.h"

Texture::Texture(const char * path) {
	// Generate image data
	glGenTextures(1, &ID);
	bindObject();
	createTexture(path);
}

void Texture::createTexture(const char * path) {
	unsigned char* data;
	bindObject();
	// Generate image data
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	int format;
	switch (nrChannels) {
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		format = GL_RGB;
	}
	if (!data && path != "n/a") {
		std::cout << "Failed to load texture with path: " << path << std::endl;
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