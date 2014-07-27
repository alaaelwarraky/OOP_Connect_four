#include "stdafx.h"
#include "BOARD.h"
#include "SDL_Setup.h"

BOARD::BOARD()
{
	quit = false;
	//csdl_setup.ScreenWidth = 0;
	csdl_setup = new CSDL_Setup(&quit);

	board_image = IMG_LoadTexture(csdl_setup->GetRenderer, "Board.png");
	
	player_1_image = IMG_LoadTexture(csdl_setup->GetRenderer, "player 1.png");
	player_1_win = IMG_LoadTexture(csdl_setup->GetRenderer, "player 1_win.png");
	
	noWinner = IMG_LoadTexture(csdl_setup->GetRenderer, "nowinner.png");
	
	player_2_image = IMG_LoadTexture(csdl_setup->GetRenderer, "player 2.png");
	player_2_win = IMG_LoadTexture(csdl_setup->GetRenderer, "player 2_win.png");
	
	screen_rect.x = 3;//the x location of the rectangle's upper left corner
	screen_rect.y = 0;//the y location of the rectangle's upper left corner
	screen_rect.w = ScreenWidth;//the width of the rectangle
	screen_rect.h = ScreenHeight;//the height of the rectangle

	coin_rect.x = 8;//the x location of the rectangle's upper left corner
	coin_rect.y = 10;//the y location of the rectangle's upper left corner
	coin_rect.w = 96;//the width of the rectangle
	coin_rect.h = 86;//the height of the rectangle
}


BOARD::~BOARD()
{
	SDL_DestroyTexture(board_image);
	SDL_DestroyTexture(player_1_image);
	SDL_DestroyTexture(player_1_win);
	SDL_DestroyTexture(player_2_win);
	SDL_DestroyTexture(player_2_image);
	SDL_DestroyTexture(noWinner);

}
void GameLoop()
{

}