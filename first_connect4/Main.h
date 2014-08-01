#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include"Sprite.h"
using namespace std;
class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHight);
	~CMain();
	void GameLoop();
	int drop(int col);
	bool check(int a, int b);
	struct cell
	{
		int in;
		char player;
	};
	cell place[6][7];
	vector<SDL_Rect>Rect1, Rect2;
	int number_of_coin = 0;
	bool winner;
private:
	int ScreenWidth;
	int ScreenHeight;
	bool quit;
	
	CSprite* board;

	CSprite* red_coin;

	CSprite* yellow_coin;

	CSprite* red_win;

	CSprite* yellow_win;

	CSprite* no_winner;

	CSDL_Setup* csdl_setup;
	
	int timeCheck;
	int MouseX;
	int MouseY;
	bool follow;
};

