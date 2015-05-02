#include <windows.h>
#include "src/GameManager.h"

int main()
{
	try {
		GameManager game({ 1280, 720 }, false);
		while (game.isRunning())
		{
			game.runFrame();
		}
	} catch (std::exception& e) {
		// error handling is done outside the game source files, to easily rewrite the game to another OS
		MessageBox(NULL, e.what(), "Error!", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}