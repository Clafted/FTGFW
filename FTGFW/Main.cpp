#include "FTGFWProgram.h"
#include "Demo/DefaultScene.h"

int main() {
	FTGFWProgram program;
	if (program.initProgram() == -1) {
		std::cout << "ERROR OCCURED INITIALIZING THE PROGRAM" << std::endl;
		return -1;
	}
	if (program.initRenderLoop(new DefaultScene()) == -1) {
		std::cout << "ERROR OCCURED IN THE RENDER LOOP" << std::endl;
		return -1;
	}
	return 0;
}