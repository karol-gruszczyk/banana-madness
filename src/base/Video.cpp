#include "Video.h"

Video::Video(std::string videoPath)
{
	load(videoPath);
}

void Video::load(std::string videoPath)
{
	if (!movieHandle.openFromFile(videoPath))
		throw FileLoadException(videoPath);
	// windowHandle should be at this point initialized
	movieHandle.fit({ 0, 0, (float)windowHandle->getSize().x, (float)windowHandle->getSize().y });
}

void Video::render()
{
	movieHandle.update();
	windowHandle->draw(movieHandle);
}

void Video::play()
{
	movieHandle.play();
}

void Video::stop()
{
	movieHandle.stop();
}

bool Video::isPlaying()
{
	return movieHandle.getStatus() == sfe::Status::Playing;
}
