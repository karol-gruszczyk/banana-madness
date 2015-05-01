#include "Intro.h"


Intro::Intro(std::string introSoundFilename)
{
	if (!musicHandle.openFromFile(introSoundFilename))
		throw FileLoadException(introSoundFilename);
}

void Intro::render(BananaMadness::GameState& gameState)
{
	if (musicHandle.getStatus() != sf::Sound::Status::Playing)
	{
		if (musicPlayed)
		{
			gameState = BananaMadness::GameState::IN_MENU;
			musicPlayed = false;
		}
		musicHandle.play();
		musicPlayed = true;
	}
}
