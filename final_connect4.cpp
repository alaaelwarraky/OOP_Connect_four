#include<iostream>
#include <sstream>
#include<vector>
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;
const int SCREEN_WIDTH = 1073;
const int SCREEN_HEIGHT = 571;
bool winner = false;
int number_of_coin = 0;
struct cell
{
	int in;
	char player;
};
cell place[6][7];
SDL_Texture* player_1_image[42];
bool press = false;
vector<SDL_Rect>Rect1, Rect2;
//**********
// drop coin
//**********
int drop(int j)
{
	int i;
	for (i = 1; i<7; i++)//<==
	{
		if (place[i - 1][j].in == 1)//that is the place which coin in it
		{
			if (i - 2 >= 0)//i will check if the next place is realy (greater than zero)
			{
				place[i - 2][j].in = 1;//<============= i will put the coin in the next place that empty
			}
			return i;// that will return the numper of row that i will drop the coin in it
		}
	}
	place[i - 2][j].in = 1;//<<<<<<<<<<<<---------------------------that will put the coin in the last place
	return i; //that will return the numper of row that i will drop the coin in it
}
//************
//check winner
//************
bool check(int a, int b)
{
	if (place[a][b].in == 1)
	{
		int vertical = 1;//(|)
		int horizontal = 1;//(-)
		int diagonal1 = 1;//(\)
		int diagonal2 = 1;//(/)
		char player = place[a][b].player;
		int i;//vertical
		int j;//horizontal
		//check for vertical(|)
		for (i = a + 1; place[i][b].player == player && i < 6; i++, vertical++);//Check down
		for (i = a - 1; place[i][b].player == player && i >= 0; i--, vertical++);//Check up
		if (vertical >= 4)return true;
		//check for horizontal(-)
		for (j = b - 1; place[a][j].player == player && j >= 0; j--, horizontal++);//Check left
		for (j = b + 1; place[a][j].player == player && j < 7; j++, horizontal++);//Check right
		if (horizontal >= 4) return true;
		//check for diagonal 1 (\)
		for (i = a - 1, j = b - 1; place[i][j].player == player && i >= 0 && j >= 0; diagonal1++, i--, j--);//up and left
		for (i = a + 1, j = b + 1; place[i][j].player == player && i < 6 && j < 7; diagonal1++, i++, j++);//down and right
		if (diagonal1 >= 4) return true;
		//check for diagonal 2(/)
		for (i = a - 1, j = b + 1; place[i][j].player == player && i >= 0 && j < 7; diagonal2++, i--, j++);//up and right
		for (i = a + 1, j = b - 1; place[i][j].player == player && i < 6 && j >= 0; diagonal2++, i++, j--);//up and left
		if (diagonal2 >= 4) return true;
		return false;
	}
}
int main(int argc, char* argv[])
{
	bool quit = false; // the program open until quit = true 
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Init(SDL_INIT_VIDEO);
	//**************************************************************************************************************
	//SDL_Window is the struct that hold all info about the Window itself. Size, position, full screen, borders etc..
	//**************************************************************************************************************
	SDL_Window* window = NULL; //assign NULL to the window until upload

	window = SDL_CreateWindow(" CONNECT FOUR ", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); //upload window
	// if window still null thats mean it's not upload
	if (window == NULL)
	{
		std::cout << "window couldn't be created " << std::endl;
		return 0;
	}

	SDL_Renderer* gRenderer = NULL;

	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Event* mainEvent = new SDL_Event();//to defention the use of mouse  keyboard or joystick 
	//******************************************************/
	/*SDL_Texture --> A structure that contains an efficient,
	driver-specific representation of pixel data*/
	/*******************************************************/
	// pixel data for the blue board of the game
	SDL_Texture* board_image = NULL;
	board_image = IMG_LoadTexture(gRenderer, "Board.png");
	// if the blue board still null thats mean it's not upload
	if (board_image == NULL)
	{
		std::cout << "couldn't load board ! " << std::endl;
	}
	//*******************************************************
	// SDL_Rect --> defines a rectangular area of the screen
	//*******************************************************
	SDL_Rect board_rect;
	board_rect.x = 3;//the x location of the rectangle's upper left corner
	board_rect.y = 0;//the y location of the rectangle's upper left corner
	board_rect.w = SCREEN_WIDTH;//the width of the rectangle
	board_rect.h = SCREEN_HEIGHT;//the height of the rectangle

	//draw player_1
	// pixel data for the red coin of the game
	SDL_Texture* player_1_image = NULL;
	player_1_image = IMG_LoadTexture(gRenderer, "player 1.png");

	// pixel data for the picture that celebrate with player 1 because he won :D
	SDL_Texture* player_1_win = NULL;
	player_1_win = IMG_LoadTexture(gRenderer, "player 1_win.png");
	// if the RED COIN still null thats mean it's not upload
	if (player_1_image == NULL)
	{
		std::cout << "couldn't load player_1 ! " << std::endl;
	}
	// if the "PINK IMAGE WITH SMILE FACE"  still null thats mean it's not upload
	if (player_1_win == NULL)
	{
		std::cout << "couldn't load WINNER ! " << std::endl;
	}
	SDL_Texture* noWinner = NULL;
	noWinner = IMG_LoadTexture(gRenderer, "nowinner.png");

	//********************************************************************
	// SDL_Rect --> defines a rectangular area of the PICTURE THAT I LOAD
	//********************************************************************
	SDL_Rect player_1_rect, player_2_rect, nowinner_rect;// , player_1_window_rect, player_2_window_rect;
	// pixel data for the YELLOW coin of the game
	SDL_Texture* player_2_image = NULL;
	player_2_image = IMG_LoadTexture(gRenderer, "player 2.png");
	// pixel data for the picture that celebrate with player 2 because he won :D
	SDL_Texture* player_2_win = NULL;
	player_2_win = IMG_LoadTexture(gRenderer, "player 2_win.png");

	// if the YELLOW COIN still null thats mean it's not upload
	if (player_2_image == NULL)
	{
		std::cout << "couldn't load player_2 ! " << std::endl;
	}
	// if the "PINK IMAGE WITH SMILE FACE"  still null thats mean it's not upload
	if (player_2_win == NULL)
	{
		std::cout << "couldn't load WINNER ! " << std::endl;
	}

	player_1_rect.x = 8;//the x location of the rectangle's upper left corner
	player_1_rect.y = 10;//the y location of the rectangle's upper left corner
	player_1_rect.w = 96;//the width of the rectangle
	player_1_rect.h = 86;//the height of the rectangle

	player_2_rect.x = 8;//the x location of the rectangle's upper left corner
	player_2_rect.y = 10;//the y location of the rectangle's upper left corner
	player_2_rect.w = 96;//the width of the rectangle
	player_2_rect.h = 86;//the height of the rectangle

	nowinner_rect.x = 0;
	nowinner_rect.y = 0;
	nowinner_rect.w = SCREEN_WIDTH;
	nowinner_rect.h = SCREEN_HEIGHT;
	//THE GAME LOOP
	while (!quit && mainEvent->type != SDL_QUIT)//THE GAME WILL BE ON WHILE QUIT = FALSE
	{
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(gRenderer);
		if (winner == false)
		{
			SDL_RenderCopy(gRenderer, board_image, NULL, &board_rect); //Implementation draw the board
			for (int j = 0; j < Rect1.size(); j++)
			{
				SDL_RenderCopy(gRenderer, player_1_image, NULL, &Rect1[j]);//save red coin in the vector 1

			}
			for (int j = 0; j < Rect2.size(); j++)
			{
				SDL_RenderCopy(gRenderer, player_2_image, NULL, &Rect2[j]);//save the yellow coin in the vector two
			}
			if (number_of_coin % 2 == 0)
			{
				SDL_RenderCopy(gRenderer, player_1_image, NULL, &player_1_rect);//draw the red coin if the number of coin is even number
			}
			else
			{
				SDL_RenderCopy(gRenderer, player_2_image, NULL, &player_2_rect);//draw the yellow coin if the number of coin is odd number
			}


		}
		else if (winner == true)//if one of the player win
		{
			
			//Update screen
			if (number_of_coin % 2 != 0)
				SDL_RenderCopy(gRenderer, player_2_win, NULL, &nowinner_rect);//draw the funny picture of player 2 when the number is odd
			if (number_of_coin % 2 == 0)
				SDL_RenderCopy(gRenderer, player_1_win, NULL, &nowinner_rect);//draw the funny picture of player 1 when the number is even
			SDL_RenderPresent(gRenderer);//upload the picture
			if (number_of_coin % 2 == 0)
			{   //  use the keyboard 
				switch (mainEvent->type)
				{
				case SDL_KEYDOWN:
					switch (mainEvent->key.keysym.sym)
					{
					case SDLK_SPACE:// press space when you want to play again
						//select the area of red coin again
						player_1_rect.x = 8;
						player_1_rect.y = 10;
						player_1_rect.w = 96;
						player_1_rect.h = 86;
						Rect1.clear();//clear the vector of red coin to begain with empty board
						Rect2.clear();//clear the vector of yellow coin to begain with empty board
						for (int i = 0; i < 6; i++)
						for (int j = 0; j < 7; j++)
						{
							place[i][j].in = 0;//clear the int array to begain with empty board
							place[i][j].player = ' ';//clear the char array to begain with empty board
						}
						SDL_RenderCopy(gRenderer, board_image, NULL, &board_rect);//draw the board
						winner = false;// because replay all the game loop again
						break;

					}
				}
			}
			else if (number_of_coin % 2 != 0)
			{
				switch (mainEvent->type)
				{
				case SDL_KEYDOWN:
					switch (mainEvent->key.keysym.sym)
					{
					case SDLK_SPACE:
						//select the area of yellow coin again
						player_2_rect.x = 8;
						player_2_rect.y = 10;
						player_2_rect.w = 96;
						player_2_rect.h = 86;
						winner = false;
						Rect1.clear();
						Rect2.clear();
						for (int i = 0; i < 6; i++)
						for (int j = 0; j < 7; j++)
						{
							place[i][j].in = 0;
							place[i][j].player = ' ';
						}
						SDL_RenderCopy(gRenderer, board_image, NULL, &board_rect);
					}
				}
			}
			continue;
		}
		// use keyboard
		switch (mainEvent->type)
		{
		case SDL_KEYDOWN:
			switch (mainEvent->key.keysym.sym)
			{
			case SDLK_a://press LEFT '<--'
				if (number_of_coin % 2 == 0 && player_1_rect.x > 8)//RED COIN "even number" and don't move out the board
					player_1_rect.x -= 100;//MOVE THE RED COIN -100 WHEN PRESS <--
				if (number_of_coin % 2 != 0 && player_2_rect.x > 8)//YELLOW COIN "odd number" and don't move out the board
					player_2_rect.x -= 100;//MOVE THE YELLOW COIN -100 WHEN PRESS <--
				break;
			case SDLK_d://PRESS RIGHT '-->'
				if (number_of_coin % 2 == 0 && player_1_rect.x <= 590)//RED COIN "even number" and don't move out the board
					player_1_rect.x += 100;//MOVE THE RED COIN +100 WHEN PRESS -->
				if (number_of_coin % 2 != 0 && player_2_rect.x <= 590)//YELLOW COIN "odd number" and don't move out the board
					player_2_rect.x += 100;//MOVE THE yellow COIN +100 WHEN PRESS -->
				break;
			case SDLK_SPACE:
				if (number_of_coin % 2 == 0 && winner == false)
				{
					if (player_1_rect.y >= 10)
					{
						int col = (player_1_rect.x - 8) / 100;
						int row = drop(col);
						if (row != 1)
						{
							place[row - 2][(player_1_rect.x - 8) / 100].player = 'A';
							player_1_rect.y += 66 * row;
							player_1_rect.y -= (6 - row) * 13;
							Rect1.push_back(player_1_rect);//push the coin in the vector
							//draw the yellow coin after the red coin drop
							player_2_rect.x = 8;
							player_2_rect.y = 10;
							player_2_rect.w = 96;
							player_2_rect.h = 86;

						}
						else
						{
							break;//if drop in illegal place will break
						}

						winner = check(row - 2, col);//check the winner
						if (winner == true)
						{  //load the winner picture
							player_1_rect.x = 0;
							player_1_rect.y = 0;
							player_1_rect.w = SCREEN_WIDTH;
							player_1_rect.h = SCREEN_HEIGHT;
							SDL_RenderCopy(gRenderer, player_1_win, NULL, &player_1_rect);
							break;
						}

					}
				}
				else if (number_of_coin % 2 != 0 && winner == false)
				{
					if (player_2_rect.y >= 10)
					{
						int col = (player_2_rect.x - 8) / 100;
						int row = drop(col);
						if (row != 1)
						{
							place[row - 2][(player_2_rect.x - 8) / 100].player = 'B';
							player_2_rect.y += 66 * row;
							player_2_rect.y -= (6 - row) * 13;
							Rect2.push_back(player_2_rect);
							//draw the red coin after the yellow coin drop
							player_1_rect.x = 8;
							player_1_rect.y = 10;
							player_1_rect.w = 96;
							player_1_rect.h = 86;

						}
						else
						{
							break;//if drop in illegal place will break
						}

						winner = check(row - 2, col);
						if (winner == true)
						{ //load the winner picture
							player_2_rect.x = 0;
							player_2_rect.y = 0;
							player_2_rect.w = SCREEN_WIDTH;
							player_2_rect.h = SCREEN_HEIGHT;
							SDL_RenderCopy(gRenderer, player_2_win, NULL, &player_2_rect);
							break;
						}

					}
				}
				if (!winner)
					number_of_coin++;//put one to the coin
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if (number_of_coin == 42 && winner == false)
		{

			SDL_RenderCopy(gRenderer, noWinner, NULL, &nowinner_rect);
			SDL_RenderPresent(gRenderer);

			switch (mainEvent->type)
			{
			case SDL_KEYDOWN:
				switch (mainEvent->key.keysym.sym)
				{
				case SDLK_SPACE:// press space when you want to play again
					//select the area of red coin again

					Rect1.clear();//clear the vector of red coin to begain with empty board
					Rect2.clear();//clear the vector of yellow coin to begain with empty board
					for (int i = 0; i < 6; i++)
					for (int j = 0; j < 7; j++)
					{
						place[i][j].in = 0;//clear the int array to begain with empty board
						place[i][j].player = ' ';//clear the char array to begain with empty board
					}
					number_of_coin = 0;
					SDL_RenderCopy(gRenderer, board_image, NULL, &board_rect);//draw the board
					player_1_rect.x = 8;
					player_1_rect.y = 10;
					player_1_rect.w = 96;
					player_1_rect.h = 86;
				}
			}
		}
		//Update screen
		/* functions draws to a hidden target.
		This functions will take all of that and draw it in the window tied to the renderer*/
		SDL_RenderPresent(gRenderer);
	}

	SDL_DestroyWindow(window);//Use this function to destroy a window.
	SDL_DestroyRenderer(gRenderer);//Use this function to destroy the rendering context for a window and free associated textures
	delete mainEvent;
	//system("pause");
	return 0;
}