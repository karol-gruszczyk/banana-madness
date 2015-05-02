#include "Intro.h"


Intro::Intro(std::string introSoundFilename)
{
	if (!musicHandle.openFromFile(introSoundFilename))
		throw FileLoadException(introSoundFilename);
}

void Intro::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys)
{
	if (musicHandle.getStatus() != sf::Sound::Status::Playing)
	{
		if (musicPlayed)
		{
			gameState = BananaMadness::GameState::IN_MENU;
			musicPlayed = false;
			return;
		}
		musicHandle.play();
		musicPlayed = true;
	}
}
