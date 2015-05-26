#pragma once

#include <sfeMovie/Movie.hpp>

#include <src/base/Drawable.h>

class Video : public Drawable
{
public:
	Video() {}
	Video(std::string videoPath);
	void load(std::string videoPath);

	void render();
	void play();
	void stop();
	bool isPlaying();
private:
	sfe::Movie movieHandle;
};

