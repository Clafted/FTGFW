#include "Renderer.hpp"
#include "../openGLObjects/GLIncludes.hpp"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {
	// Use Shaders
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shader.ID);

	shader.setInt("material.u_currentTexture", 0);
	shader.setInt("material.u_specularMap", 1);
};
Renderer::~Renderer() {};

void Renderer::terminate() {
	delete instance;
}

Renderer* Renderer::Instance() {
	if (!Renderer::instance) instance = new Renderer();
	return instance;
}

void Renderer::updateMatrices(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPos) {
	this->view = view;
	this->projection = projection;
	this->cameraPos = cameraPos;
}

void Renderer::renderFrame(GLFWwindow * window) {
	// Update the camera's (view) uniform variables
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setVector3("cameraPos", cameraPos);

	// Update light variables
	// ------------------------------------------------------------------------------------------
	std::string iterator;
	for (int i = 0; i < 4; i++) {
		if (!lights[i]) continue;

		iterator = "pointLights[" + std::to_string(i) + "]";
		shader.setVector3(iterator + ".pos", lights[i]->pos);
		shader.setVector3(iterator + ".lightColor", lights[i]->lightColor);
		shader.setFloat(iterator + ".intensity", lights[i]->intensity);
		shader.setFloat(iterator + ".ambientStrength", lights[i]->ambientStrength);
		shader.setFloat(iterator + ".diffuseStrength", lights[i]->diffuseStrength);
		shader.setFloat(iterator + ".specularStrength", lights[i]->specularStrength);
	}

	// Clear the screen
	glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render every Entity
	// ------------------------------------------------------------------------------------------
	for (RenderComponent* renderComponent : renderComponents) {
		// Create model transformation matrix (NOTE: Order of calculations is SCALE, ROTATE, then TRANSLATE)
		model = glm::translate(glm::mat4(1.0f), renderComponent->modelPos);
		model = glm::rotate(model, renderComponent->rotationAngle, renderComponent->rotationAxis);
		model = glm::scale(model, renderComponent->scale);

		// Update model transformation matrix
		shader.setMat4("model", model);

		// Render
		renderComponent->vao.bindObject();
		glActiveTexture(GL_TEXTURE0);
		renderComponent->diffuseMap.bindObject();
		glActiveTexture(GL_TEXTURE1);
		renderComponent->specularMap.bindObject();
		glDrawElements(GL_TRIANGLES, renderComponent->ebo.getNumIndices(), GL_UNSIGNED_INT, 0);
	}
	// Switch to the newly rendered frame
	glfwSwapBuffers(window);
}