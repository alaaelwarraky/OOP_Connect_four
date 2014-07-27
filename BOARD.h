#pragma once
#include "SDL_Setup.h"
class BOARD
{
public:
	BOARD();
	~BOARD();
	void GameLoop();
	int ScreenWidth;
	int ScreenHeight;
private:
	bool quit;
	CSDL_Setup* csdl_setup;
	SDL_Texture* board_image;
	SDL_Texture* player_1_image;
	SDL_Texture* player_1_win;
	SDL_Texture* player_2_image;
	SDL_Texture* player_2_win;
	SDL_Texture* noWinner;
	SDL_Rect screen_rect;
	SDL_Rect coin_rect;

};

