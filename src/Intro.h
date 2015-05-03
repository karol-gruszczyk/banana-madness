#pragma once

#include "Video.h"

class Intro
{
public:
	Intro(std::string videoPath);

	void runFrame(BananaMadness::GameState& gameState, std::vector<unsigned> pressedKeys);
private:
	Video videoHandle;
	bool videoPlayed;
};

