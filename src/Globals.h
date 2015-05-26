#pragma once

#ifdef _DEBUG
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_MENU
#else
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_INTRO
#endif

#define WINDOW_TITLE "Banana Madness: a journey into insanity"
#define INTRO_VIDEO "data/video/intro.mp4"
#define MENU_BACKGROUND "data/img/gui/menu.png"
#define MENU_MUSIC "data/music/menu.wav"
#define BUTTON_IMAGE "data/img/gui/button.png"
#define BUTTON_SELECTED_IMAGE "data/img/gui/monkey.png"
#define BUTTON_FONT "data/cakenom.ttf"
#define BUTTON_CLICK_SOUND "data/sound/click.wav"
#define BUTTON_HOVER_SOUND "data/sound/hover.wav"
#define LEVEL_0 "data/maps/level1.bm"

namespace BananaMadness
{
	enum GameState { IN_INTRO, LOADING, IN_MENU, IN_GAME, PAUSED };
}
extern const char* levels[2];
