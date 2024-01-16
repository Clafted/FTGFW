#include <iostream>

#include "FTGFWProgram.hpp"
#include "scene/SceneManager.hpp"
#include "DefaultScene.hpp"
#include "LandGenerationScene.hpp"

int main() {
	
	if (FTGFWProgram::Instance()->initProgram(1280, 720) == -1) {
		std::cout << "ERROR OCCURED INITIALIZING THE PROGRAM" << std::endl;
		return -1;
	}
	SceneManager::Instance()->addScene("DefaultScene", new DefaultScene());
	SceneManager::Instance()->addScene("LandGenerationScene", new LandGenerationScene());
	SceneManager::Instance()->setScene("LandGenerationScene");
	SceneManager::Instance()->getCurrentScene()->setScreenDimensions(1280, 720);

	if (FTGFWProgram::Instance()->initRenderLoop("LandGenerationScene") == -1) {
		std::cout << "ERROR OCCURED IN THE RENDER LOOP" << std::endl;
		return -1;
	}
	std::cout << "Ending program..." << std::flush;
	FTGFWProgram::terminate();
	SceneManager::terminate();
	Renderer::terminate();
	return 0;
}