#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../shaders/Shader.hpp"
#include "../component/CameraComponent.hpp"
#include "../component/RenderComponent.hpp"
#include "../component/LightComponents.hpp"
#include "System.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <array>
#include <string>

class RenderSystem : public System {
public:
	
	RenderSystem(ComponentManager& componentManager, SceneManager& sceneManager) : System(componentManager, sceneManager) {};
	~RenderSystem();
	void update(GLFWwindow * window, float deltaTime);
	void updateMatrices(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos);
	void addShader(std::string vertexShaderPath, std::string fragmentShaderPath);

private:
	Shader *shader = nullptr;
	glm::mat4 model = glm::mat4(0.0f);
	glm::mat4 projection = glm::mat4(0.0f);
	glm::mat4 view = glm::mat4(0.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f);
};

#endif