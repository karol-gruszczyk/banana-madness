#include "Intro.h"


Intro::Intro(std::string introSoundFilename)
{
	if (!musicHandle.openFromFile(introSoundFilename))
		throw FileLoadException(introSoundFilename);
}

bool Intro::render(sf::RenderWindow& windowHandle)
{
	if (musicHandle.getStatus() != sf::Sound::Status::Playing)
	{
		if (musicPlayed)
			return true;
		musicHandle.play();
		musicPlayed = true;
	}
	return false;
}
