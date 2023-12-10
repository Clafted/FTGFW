#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGLObject.hpp"
#include "stb_image.h"
#include <string>

/*
 * The Texture class simplifies the use of OpenGL Texture objects.
 * 
 * @author Noah Perez
 */
class Texture : public OpenGLObject {

public:
	Texture(const char* path) {
		// Generate image data
		data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data) {
			glGenTextures(1, &ID);
			bindObject();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);		// Add image data to bound texture
			glGenerateMipmap(GL_TEXTURE_2D);																// Generate mipmaps for different distances
		} else {
			std::cout << "Failed to load texture with path: " << path << std::endl;
		}
		stbi_image_free(data);
	}
	~Texture(){}

	inline void bindObject() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	inline void unbindObject() {}

private:
	int width, height, nrChannels;
	unsigned char* data;
};

#endif