#pragma once

#include <ctime>

#ifdef _DEBUG
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_MENU
#else
	#define INITIAL_GAME_STATE BananaMadness::GameState::IN_INTRO
#endif

#define WINDOW_TITLE "Banana Madness: a journey into insanity"
#define INTRO_VIDEO "data/video/intro.mp4"
#define MENU_BACKGROUND_PATH "data/img/gui/menu.png"
#define MENU_MUSIC_PATH "data/music/menu.wav"
#define BUTTON_IMAGE_PATH "data/img/gui/button.png"
#define BUTTON_SELECTED_IMAGE_PATH "data/img/gui/monkey.png"
#define BUTTON_FONT "data/cakenom.ttf"
#define BUTTON_CLICK_SOUND "data/sound/click.wav"
#define BUTTON_HOVER_SOUND "data/sound/hover.wav"
#define GAME_OVER_SOUND_PATH "data/sound/gameover.wav"
#define HEADER_FONT_PATH "data/rockgarage.ttf"
#define SIMPLE_FONT_PATH "data/arial.ttf"
#define LEVEL_CLEARED_SOUND_PATH "data/sound/level_cleared.wav"

#define GRAVITY 9.81f
#define MAX_CHARACTER_SPEED 750.f
#define PLAYER_JUMP_SPEED 2000.f
#define PLAYER_WALK_SPEED 0.6f
#define GAME_OVER_DELAY 3.75f

#define ENEMY_MOVING_SPEED 0.5f
#define ENEMY_JUMP_SPEED 2000.f

#define SPRITE_DELTA_TIME 0.05f
#define EASY_GAME_URL "http://www.gry.pl/gra/prawdziwe-fryzury-barbie"

namespace BananaMadness
{
	enum GameState { IN_INTRO, IN_MENU, IN_GAME, PAUSED, GAME_OVER, LEVEL_CLEARED };
}

#define NUM_LEVELS 2
extern const char* levels[2];

extern clock_t lastFrameTime;
extern float deltaTime;
