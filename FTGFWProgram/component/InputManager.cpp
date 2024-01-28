#include "InputManager.hpp"
#include <iostream>
std::map<int, int> InputManager::mouseButtons = {
	{ GLFW_MOUSE_BUTTON_RIGHT, GLFW_KEY_UNKNOWN },
	{ GLFW_MOUSE_BUTTON_LEFT, GLFW_KEY_UNKNOWN },
	{ GLFW_MOUSE_BUTTON_MIDDLE, GLFW_KEY_UNKNOWN },
};

InputManager* InputManager::Instance() {
	if (!instance) instance = new InputManager();
	return instance;
}

void InputManager::terminate() {
	delete instance;
}

InputManager::InputManager() {};
InputManager::~InputManager() {};

int InputManager::getButton(int button) {
	return mouseButtons.at(button);
}

void InputManager::update() {
	if (mousePosX == prevMousePosX) mouseMoveX = 0.0f;
	if (mousePosY == prevMousePosY) mouseMoveY = 0.0f;
	prevMousePosX = mousePosX;
	prevMousePosY = mousePosY;
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	mouseButtons.find(button)->second = action;
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	instance->mouseMoveX = -(instance->mousePosX - (float)xPos);
	instance->mouseMoveY = instance->mousePosY - (float)yPos;
	instance->mousePosX = (float)xPos;
	instance->mousePosY = (float)yPos;
}