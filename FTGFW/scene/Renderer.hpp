#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <array>

#include "../shaders/Shader.hpp"
#include "../component/RenderComponent.hpp"
#include "LightCasters.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
	std::vector<RenderComponent*> renderComponents = {};
	std::array<PointLight*, 4> lights = {};

	static Renderer* Instance();
	static void terminate();
	void renderFrame(GLFWwindow * window);
	void updateMatrices(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos);

private:
	Shader shader = Shader("./shaders/vertex.vert", "./shaders/fragment.frag");;
	glm::mat4 model = glm::mat4(0.0f);
	glm::mat4 projection = glm::mat4(0.0f);
	glm::mat4 view = glm::mat4(0.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f);

	~Renderer();
	Renderer();
	static Renderer* instance;
};

#endif