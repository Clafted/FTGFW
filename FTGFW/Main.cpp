#include "FTGFWProgram.hpp"
#include "Demo/DefaultScene.hpp"
#include "Demo/LandGenerationScene.hpp"

int main() {
	if (FTGFWProgram::Instance()->initProgram() == -1) {
		std::cout << "ERROR OCCURED INITIALIZING THE PROGRAM" << std::endl;
		return -1;
	}
	if (FTGFWProgram::Instance()->initRenderLoop(new LandGenerationScene(FTGFWProgram::Instance()->screenWidth, FTGFWProgram::Instance()->screenHeight)) == -1) {
		std::cout << "ERROR OCCURED IN THE RENDER LOOP" << std::endl;
		return -1;
	}
	std::cout << "Ending program..." << std::flush;
	FTGFWProgram::Instance()->terminate();
	return 0;
}