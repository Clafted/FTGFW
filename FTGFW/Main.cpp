#include "FTGFWProgram.hpp"
#include "Demo/DefaultScene.hpp"
#include "Demo/LandGenerationScene.hpp"
#include "scene/SceneManager.hpp"

int main() {
	if (FTGFWProgram::Instance()->initProgram() == -1) {
		std::cout << "ERROR OCCURED INITIALIZING THE PROGRAM" << std::endl;
		return -1;
	}
	SceneManager::Instance()->addScene("DefaultScene", new DefaultScene());
	SceneManager::Instance()->addScene("LandGenerationScene", new LandGenerationScene());
	SceneManager::Instance()->setScene("LandGenerationScene");
	SceneManager::Instance()->getCurrentScene()->setScreenDimensions(FTGFWProgram::Instance()->screenWidth, FTGFWProgram::Instance()->screenHeight);

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