#pragma once

#include <src/base/Video.h>

class Intro
{
public:
	Intro(std::string videoPath);

	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys);
	void stopVideo();
private:
	Video videoHandle;
	bool videoPlayed;
};

