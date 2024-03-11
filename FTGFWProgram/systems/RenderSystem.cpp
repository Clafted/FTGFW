#include "RenderSystem.hpp"
#include "../../third_party/GLIncludes.hpp"
#include <fstream>
#include <string>

RenderSystem::~RenderSystem() {
	delete shader;
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
	if (!(componentManager.getComponentMap<CameraComponent>() && shader)) return;
	//Update camera variables
	auto camera = std::dynamic_pointer_cast<CameraComponent>(componentManager.getComponentMap<CameraComponent>()->begin()->second);
	view = camera->lookAt();
	// Update the camera's (view) uniform variables
	shader->setMat4("projection", camera->projectionMatrix);
	shader->setMat4("view", view);
	shader->setVector3("cameraPos", camera->pos);
	// Update light variables
	// ------------------------------------------------------------------------------------------
	int counter = 0;
	std::string iterator;
	std::shared_ptr<PointLight> light;
	if (componentManager.getComponentMap<LightComponent>()) {
		for (auto i = componentManager.getComponentMap<LightComponent>()->begin(); i != componentManager.getComponentMap<LightComponent>()->end(); i++) {
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
	// Render every Entity
	// ------------------------------------------------------------------------------------------
	auto renderComponents = componentManager.getComponentMap<RenderComponent>();
	std::shared_ptr<RenderComponent> rC;
	for (auto i = renderComponents->begin(); i != renderComponents->end(); i++) {
		rC = std::dynamic_pointer_cast<RenderComponent>(i->second);
		model = glm::translate(glm::mat4(1.0f), rC->modelPos);
		model = glm::rotate(model, rC->rotationAngle, rC->rotationAxis);
		model = glm::scale(model, rC->scale);
		// Update model transformation matrix
		shader->setMat4("model", model);
		shader->setFloat("u_material.shininess", 65.0f);
		// Bind every texture in the RenderComponent
		int diffuseCounter = 0, specularCounter = 0;
		for (int i = 0; i < rC->textures.size(); i++) 
		{
			switch (rC->textures[i].getType()) 
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
			glBindTexture(GL_TEXTURE_2D, rC->textures[i].ID);
		}
		// Render
		rC->vao.bindObject();
		glDrawElements(GL_TRIANGLES, rC->ebo.getNumIndices(), GL_UNSIGNED_INT, 0);
	}
	// Switch to the newly rendered frame
	glfwSwapBuffers(window);
}

void RenderSystem::addShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	if (!std::fstream(vertexShaderPath).good() || !std::fstream(fragmentShaderPath).good()) {
		std::cout << "THE PROVIDED VERTEX/FRAGMENT SHADER PATH DOES NOT EXIST";
		return;
	}
	shader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	// Use Shaders
	glUseProgram(shader->ID);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}