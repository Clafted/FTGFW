#pragma once

#include "TextureMap_C.hpp"


struct Text_C : public Component
{
	TextureMap_C font;
	std::string text;
	glm::vec3 position;
	float spacing = 0.0f;
	bool stickToScreen;

	Text_C(std::string text, std::string fontMap, std::shared_ptr<Shader> shader, int letterWidth, int letterHeight, glm::vec3 position = glm::vec3(0.0f), bool stickToScreen = true)
		: text(text), font(fontMap, Texture::defaultPath, shader, letterWidth, letterHeight, 0, 26), position(position) , stickToScreen(stickToScreen)
	{
		font.scale = glm::vec3(letterWidth, letterHeight, 1.0f);
	}
};