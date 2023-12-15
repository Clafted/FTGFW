#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGLObject.hpp"
#include "stb_image.h"
#include <string>
#include <fstream>

/*
 * The Texture class simplifies the use of OpenGL Texture objects.
 * 
 * @author Noah Perez
 */
class Texture : public OpenGLObject {

public:
	Texture(const char* path) {
		// Generate image data
		glGenTextures(1, &ID);
		bindObject();
		createTexture(path);
	}

	Texture() : Texture("n/a") {}

	~Texture(){}

	inline void bindObject() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	inline void unbindObject() {}

	inline void createTexture(const char* path) {
		unsigned char* data;
		if (!std::ifstream(path).good()) {
			std::cout << "Failed to load texture with path: " << path << std::endl;
			data = stbi_load("./Textures/MissingTexture.png", &width, &height, &nrChannels, 0);
		} else {
			data = stbi_load(path, &width, &height, &nrChannels, 0);
			if (!data) {
				std::cout << "Failed to load texture with path: " << path << std::endl;
			}
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);		// Add image data to bound texture
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

private:
	int width = NULL, height = NULL, nrChannels = NULL;
};

#endif