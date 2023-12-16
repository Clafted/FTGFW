#include "FTGFWProgram.h"
#include "Demo/DefaultScene.h"

int main() {
	SceneManager::startingScene = new DefaultScene();
	FTGFWProgram program;
	if (program.initProgram() == -1) {
		std::cout << "ERROR OCCURED IN THE PROGRAM" << std::endl;
		return -1;
	}
	return 0;
}