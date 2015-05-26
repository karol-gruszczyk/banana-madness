#include "Intro.h"


Intro::Intro(std::string videoPath)
{
	videoHandle.load(videoPath);
}

void Intro::runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys)
{
	if (pressedKeys.size())
	{
		gameState = BananaMadness::GameState::IN_MENU;
		stopVideo();
	}

	videoHandle.render();
	if (!videoHandle.isPlaying())
	{
		if (videoPlayed)
		{
			gameState = BananaMadness::GameState::IN_MENU;
			videoPlayed = false;
			return;
		}
		videoPlayed = true;
		videoHandle.play();
	}
}

void Intro::stopVideo()
{
	videoHandle.stop();
}
