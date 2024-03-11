#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGLObject.hpp"
#include <string>
#include <fstream>

/*
 * The Texture class simplifies the use of OpenGL Texture objects.
 * 
 * @author Noah Perez
 */
class Texture : public OpenGLObject {
public:
	enum TextureType { DIFFUSE, SPECULAR };
	static const char* defaultPath;
	static std::string directory;

	Texture(std::string path, TextureType type = DIFFUSE);
	Texture() : Texture("n/a") {}
	~Texture(){}

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	inline std::string getPath() const { return path; }
	inline TextureType getType() const { return type; }
	inline void bindObject() { glBindTexture(GL_TEXTURE_2D, ID); }
	inline void unbindObject() {}
	
	/* Generate a texture to be used through OpenGL
	 * @param path - the path to the texture */
	void createTexture(std::string path);

private:
	int width = 0;
	int height = 0;
	int nrChannels = 0;
	TextureType type = DIFFUSE;
	std::string path;
};

#endif