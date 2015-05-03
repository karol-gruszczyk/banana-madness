#pragma once
#include "Header.h"

#ifdef _DEBUG
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_MENU
#else
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_INTRO
#endif

#define WINDOW_TITLE "Banana Madness: a journey into insanity"
#define INTRO_VIDEO "data/video/intro.avi"
#define MENU_BACKGROUND "data/img/menu.png"
#define MENU_MUSIC "data/music/menu.wav"
#define BUTTON_IMAGE "data/img/button.png"
#define BUTTON_SELECTED_IMAGE "data/img/monkey.png"
#define BUTTON_FONT "data/cakenom.ttf"
#define BUTTON_CLICK_SOUND ""
#define BUTTON_HOVER_SOUND ""
