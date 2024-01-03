#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGLObject.hpp"
#include "../third_party/stb_image.h"
#include <string>
#include <fstream>

/*
 * The Texture class simplifies the use of OpenGL Texture objects.
 * 
 * @author Noah Perez
 */
class Texture : public OpenGLObject {
public:
	static const char* defaultPath;

	Texture(const char * path);
	Texture() : Texture("n/a") {}
	~Texture(){}

	inline void bindObject() { glBindTexture(GL_TEXTURE_2D, ID); }
	inline void unbindObject() {}
	/* Generate a texture to be used through OpenGL
	 * @param path - the path to the texture */
	void createTexture(const char * path);

private:
	int width = NULL;
	int height = NULL;
	int nrChannels = NULL;
};

#endif