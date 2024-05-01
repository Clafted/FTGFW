#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../shaders/Shader.hpp"
#include "../component/CameraComponent.hpp"
#include "../component/RenderComponent.hpp"
#include "../component/Model_C.hpp"
#include "../component/Text_C.hpp"
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
	~RenderSystem();
	void update(GLFWwindow * window, float deltaTime);
	void updateMatrices(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos);
	unsigned int addShader(std::string vertexShaderPath, std::string fragmentShaderPath);

private:
	void renderComponent(RenderComponent* _C);
	void bindTextures(std::vector<Texture>& textures);
	void setTransformation(glm::vec3 position, float rotationAngle, glm::vec3 rotationAxis, glm::vec3 scale);
	void updateTextureMapBuffer(TextureMap_C* component);
	void changeShader(std::weak_ptr<Shader> newShader);

	std::unordered_map<unsigned int, Shader> shaders;
	std::shared_ptr<Shader> shader;
	glm::mat4 model = glm::mat4(0.0f);
	glm::mat4 projection = glm::mat4(0.0f);
	glm::mat4 view = glm::mat4(0.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f);
};

#endif