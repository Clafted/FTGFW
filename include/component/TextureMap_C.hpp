#pragma once

#include "TwoDimensional_C.hpp"

struct TextureMap_C : public TwoDimensional_C 
{
	int panelWidth, panelHeight;
	int index;
	int numPanels;
	int numRows, numColumns;
	double texPanelWidth, texPanelHeight;
	
	TextureMap_C(std::string diffuse, std::string specular, std::shared_ptr<Shader> shader, int panelWidth, int panelHeight, int index, int numPanels)
		: TwoDimensional_C(diffuse, specular, shader), panelWidth(panelWidth), panelHeight(panelHeight), index(index), numPanels(numPanels)
	{
		numColumns = textures[0].getWidth() / panelWidth;
		numRows = textures[0].getHeight() / panelHeight;
		texPanelWidth = panelWidth / (double)textures[0].getWidth();
		texPanelHeight = panelHeight / (double)textures[0].getHeight();
		glm::vec2 texCoords = glm::vec2((index % numColumns) * texPanelWidth, (numRows - (index / numColumns) - 1) * texPanelHeight);
		// Update VBO Buffer
		vao.bindObject();
		vbo.bindObject();
		texCoords.y += texPanelHeight;
		glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 2 * sizeof(float), &texCoords);
		texCoords.x += texPanelWidth;
		glBufferSubData(GL_ARRAY_BUFFER, 11 * sizeof(float), 2 * sizeof(float), &texCoords);
		texCoords.x -= texPanelWidth;
		texCoords.y -= texPanelHeight;
		glBufferSubData(GL_ARRAY_BUFFER, 19 * sizeof(float), 2 * sizeof(float), &texCoords);
		texCoords.x += texPanelWidth;
		glBufferSubData(GL_ARRAY_BUFFER, 27 * sizeof(float), 2 * sizeof(float), &texCoords);
	}
};