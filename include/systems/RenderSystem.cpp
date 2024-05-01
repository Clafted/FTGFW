#include "RenderSystem.hpp"
#include "../../third_party/GLIncludes.hpp"
#include <fstream>
#include <string>

RenderSystem::~RenderSystem() {
}

void RenderSystem::updateMatrices(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos) {
	this->view = view;
	this->projection = projection;
	this->cameraPos = cameraPos;
	// Update the camera's (view) uniform variables
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	shader->setVector3("cameraPos", cameraPos);
}

void RenderSystem::update(GLFWwindow * window, float deltaTime) {
	if (!componentManager->getComponentMap<CameraComponent>()) return;
	//Update camera variables
	auto camera = std::dynamic_pointer_cast<CameraComponent>(componentManager->getComponentMap<CameraComponent>()->begin()->second);
	projection = camera->projectionMatrix;
	view = camera->lookAt();
	cameraPos = camera->pos;
	
	// Update light variables
	// ------------------------------------------------------------------------------------------
	int counter = 0;
	std::string iterator;
	sPtr<PointLight> light;
	if (componentManager->getComponentMap<LightComponent>()) {
		for (auto i = componentManager->getComponentMap<LightComponent>()->begin(); i != componentManager->getComponentMap<LightComponent>()->end(); i++) {
			light = std::dynamic_pointer_cast<PointLight>(i->second);
			iterator = "pointLights[" + std::to_string(counter++) + "]";
			shader->setVector3(iterator + ".pos", light->pos);
			shader->setVector3(iterator + ".lightColor", light->lightColor);
			shader->setFloat(iterator + ".intensity", light->intensity);
			shader->setFloat(iterator + ".ambientStrength", light->ambientStrength);
			shader->setFloat(iterator + ".diffuseStrength", light->diffuseStrength);
			shader->setFloat(iterator + ".specularStrength", light->specularStrength);
		}
	}
	// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render
	// ------------------------------------------------------------------------------------------
	// Iterate through Render_C Map
	auto renderMap = componentManager->getComponentMap<RenderComponent>();
	sPtr<RenderComponent> rC;
	if (renderMap) {
		for (auto i = renderMap->begin(); i != renderMap->end(); i++) {
			if (i->second->skip) continue;
			rC = std::dynamic_pointer_cast<RenderComponent>(i->second);
			if (componentManager->hasComponentOfType<KinematicComponent>(i->first)) {
				sPtr<KinematicComponent> kC = componentManager->getComponent<KinematicComponent>(i->first);
				rC->modelPos = kC->pos;
				rC->rotationAngle = kC->rotation.x + kC->rotation.y + kC->rotation.z;
				rC->rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
			}
			renderComponent(rC.get());
		}
	}
	// Iterate through Model_C Map
	auto modelMap = componentManager->getComponentMap<Model_C>();
	sPtr<Model_C> model;
	if (modelMap) {
		for (auto i = modelMap->begin(); i != modelMap->end(); i++) {
			if (i->second->skip) continue;
			model = std::dynamic_pointer_cast<Model_C>(i->second);
			for (sPtr<RenderComponent> render : model->meshes) {
				renderComponent(render.get());
			}
		}
	}
	// Iterate through Text_C Map
	auto textMap = componentManager->getComponentMap<Text_C>();
	if (textMap)
	{
		sPtr<Text_C> text;
		glm::vec3 position;
		int index = 0;
		for (auto i = textMap->begin(); i != textMap->end(); i++) {
			text = std::dynamic_pointer_cast<Text_C>(i->second);
			position = text->position;
			// Change to different shader if necessary
			changeShader(text->font.shader);
			bindTextures(text->font.textures);
			text->font.vao.bindObject();
			for (int x = 0; x < text->text.length(); x++) {
				setTransformation(position, text->font.rotationAngle, text->font.rotationAxis, text->font.scale);
				text->font.index = (int)text->text[x] - 30;
				updateTextureMapBuffer(&text->font);
				// Render
				glDrawElements(GL_TRIANGLES, text->font.ebo.getNumIndices(), GL_UNSIGNED_INT, 0);
				position.x += text->spacing + text->font.scale.x;
			}
		}
	}
	// Switch to the newly rendered frame
	glfwSwapBuffers(window);
}

unsigned int RenderSystem::addShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	if (!std::fstream(vertexShaderPath).good() || !std::fstream(fragmentShaderPath).good()) {
		std::cout << "THE PROVIDED VERTEX/FRAGMENT SHADER PATH DOES NOT EXIST";
		return -1;
	}
	shader = std::make_shared<Shader>(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	// Use Shaders
	glUseProgram(shader->ID);

	return shader->ID;
}

void RenderSystem::renderComponent(RenderComponent* _C) {
	changeShader(_C->shader);
	// Update model transformation matrix
	setTransformation(_C->modelPos, _C->rotationAngle, _C->rotationAxis, _C->scale);
	bindTextures(_C->textures);
	// Render
	_C->vao.bindObject();
	glDrawElements(GL_TRIANGLES, _C->ebo.getNumIndices(), GL_UNSIGNED_INT, 0);
}

void RenderSystem::setTransformation(glm::vec3 position, float rotationAngle, glm::vec3 rotationAxis, glm::vec3 scale)
{
	model = glm::translate(glm::mat4(1.0f), position);
	model = glm::rotate(model, rotationAngle, rotationAxis);
	model = glm::scale(model, scale);
	shader->setMat4("model", model);
}

void RenderSystem::bindTextures(std::vector<Texture>& textures)
{
	shader->setFloat("u_material.shininess", 65.0f);
	// Bind every texture in the RenderComponent
	int diffuseCounter = 0, specularCounter = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		switch (textures[i].getType())
		{
		case Texture::DIFFUSE:
			shader->setInt("u_material.diffuseMap" + diffuseCounter++, i);
			break;
		case Texture::SPECULAR:
			shader->setInt("u_material.specularMap" + specularCounter++, i);
			break;
		default:
			shader->setInt("u_material.specularMap" + specularCounter++, i);
			break;
		}
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}
}

void RenderSystem::updateTextureMapBuffer(TextureMap_C* component)
{
	// Locate the bottom right corner of the letter
	glm::vec2 texCoords = glm::vec2((component->index % component->numColumns) * component->texPanelWidth, (component->numRows - (component->index / component->numColumns) - 1) * component->texPanelHeight);
	// Update VBO Buffer
	component->vao.bindObject();
	component->vbo.bindObject();
	texCoords.y += component->texPanelHeight;
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 2 * sizeof(float), &texCoords);
	texCoords.x += component->texPanelWidth;
	glBufferSubData(GL_ARRAY_BUFFER, 11 * sizeof(float), 2 * sizeof(float), &texCoords);
	texCoords.x -= component->texPanelWidth;
	texCoords.y -= component->texPanelHeight;
	glBufferSubData(GL_ARRAY_BUFFER, 19 * sizeof(float), 2 * sizeof(float), &texCoords);
	texCoords.x += component->texPanelWidth;
	glBufferSubData(GL_ARRAY_BUFFER, 27 * sizeof(float), 2 * sizeof(float), &texCoords);
}

void RenderSystem::changeShader(std::weak_ptr<Shader> newShader) {
	// Change to different shader if necessary
	if (!shader || shader->ID != newShader.lock()->ID) {
		shader = newShader.lock();
		glUseProgram(shader->ID);
		// Update the camera's (view) uniform variables
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setVector3("cameraPos", cameraPos);
	}
}