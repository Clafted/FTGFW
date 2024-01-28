#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>
#include "../../third_party/GLIncludes.hpp"

class InputManager {
public:
	static InputManager* Instance();
	static void terminate();

	int getButton(int button);
	inline float getMousePosX() { return mousePosX; }
	inline float getMousePosY() { return mousePosY; }
	inline float getMouseMoveX() { return mouseMoveX; }
	inline float getMouseMoveY() { return mouseMoveY; }
	void update();

	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);

private:
	InputManager();
	~InputManager();

	static InputManager* instance;
	static std::map<int, int> mouseButtons;
	float mousePosX = 0.0f, mousePosY = 0.0f, mouseMoveX = 0.0f, mouseMoveY = 0.0f;
	float prevMousePosX = 0.0f, prevMousePosY = 0.0f;
};

#endif