#include "stdafx.h"
#include "Main.h"
#include "Sprite.h"


CMain::CMain(int passed_ScreenWidth,int passed_ScreenHight)
{   
	winner = false;
	number_of_coin = 0;
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit,  ScreenWidth, ScreenHeight);
	board = new CSprite(csdl_setup->GetRenderer(),"board.png",0,0,1073,571);
	red_coin = new CSprite(csdl_setup->GetRenderer(), "player 1.png", 8, 10, 96, 86);
	yellow_coin = new CSprite(csdl_setup->GetRenderer(), "player 2.png", 8, 10, 96, 86);
	red_win = new CSprite(csdl_setup->GetRenderer(), "player 1_win.png", 0, 0, 1073, 571);
	yellow_win = new CSprite(csdl_setup->GetRenderer(), "player 2_win.png", 0, 0, 1073, 571);
	no_winner = new CSprite(csdl_setup->GetRenderer(), "nowinner.png", 0, 0, 1073, 571);

	/*timeCheck = SDL_GetTicks();
	MouseX = 0;
	MouseY = 0;
	follow = false;*/
}


CMain::~CMain()
{   //memory leaks
	delete csdl_setup;
	delete board;
	delete red_coin;
	delete yellow_coin;
	delete red_win;
	delete yellow_win;
	delete no_winner;
}


bool CMain::check(int a, int b)
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

int CMain::drop(int col)
{
	int raw;
	for (raw = 1; raw<7; raw++)//<==
	{
		if (place[raw - 1][col].in == 1)//that is the place which coin in it
		{
			if (raw - 2 >= 0)//i will check if the next place is realy (greater than zero)
			{
				place[raw - 2][col].in = 1;//<============= i will put the coin in the next place that empty
			}
			return raw;// that will return the numper of row that i will drop the coin in it
		}
	}
	place[raw - 2][col].in = 1;//<<<<<<<<<<<<---------------------------that will put the coin in the last place
	return raw; //that will return the numper of row that i will drop the coin in it
}


void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->begain();

		board->draw();
		
		for (int j = 0; j < Rect1.size(); j++)
		{
			SDL_RenderCopy(csdl_setup->GetRenderer(), red_coin->Get_image(), NULL, &Rect1[j]);//save red coin in the vector 1

		}
		for (int j = 0; j < Rect2.size(); j++)
		{
			SDL_RenderCopy(csdl_setup->GetRenderer(), yellow_coin->Get_image(), NULL, &Rect2[j]);//save the yellow coin in the vector two
		}
		if (number_of_coin % 2 == 0)
		{
			red_coin->draw();//draw the red coin if the number of coin is even number
		}
		else
		{
			yellow_coin->draw();//draw the yellow coin if the number of coin is odd number
		}

		if (number_of_coin == 42 && winner == false)
			no_winner->draw();

		csdl_setup->end();//upload the picture
		 if (winner == true)//if one of the player win
			{

				//Update screen
				if (number_of_coin % 2 == 0)
					red_win->draw();//draw the funny picture of player 2 when the number is odd
				if (number_of_coin % 2 != 0)
					yellow_win->draw();//draw the funny picture of player 2 when the number is odd
				

				csdl_setup->end();//upload the picture
				
				 if (number_of_coin % 2 == 0)
				{   //  use the keyboard 
					switch (csdl_setup->GetMainEvent()->type)
					{
					case SDL_KEYDOWN:
						switch (csdl_setup->GetMainEvent()->key.keysym.sym)
						{
						case SDLK_SPACE:// press space when you want to play again
							//select the area of red coin again
							red_coin = new CSprite(csdl_setup->GetRenderer(), "player 1.png", 8, 10, 96, 86);

							Rect1.clear();//clear the vector of red coin to begain with empty board
							Rect2.clear();//clear the vector of yellow coin to begain with empty board
							number_of_coin = 0;
							for (int i = 0; i < 6; i++)
							for (int j = 0; j < 7; j++)
							{
								place[i][j].in = 0;//clear the int array to begain with empty board
								place[i][j].player = ' ';//clear the char array to begain with empty board
							}
							board->draw();//draw the board
							winner = false;// because replay all the game loop again
							break;

						}
					}
				}

				else if (number_of_coin % 2 != 0)
				{
					switch (csdl_setup->GetMainEvent()->type)
					{
					case SDL_KEYDOWN:
						switch (csdl_setup->GetMainEvent()->key.keysym.sym)
						{
						case SDLK_SPACE:// press space when you want to play again
							//select the area of red coin again
							yellow_coin = new CSprite(csdl_setup->GetRenderer(), "player 2.png", 8, 10, 96, 86);
							winner = false;// because replay all the game loop again
							Rect1.clear();//clear the vector of red coin to begain with empty board
							Rect2.clear();//clear the vector of yellow coin to begain with empty board
							number_of_coin = 0;
							for (int i = 0; i < 6; i++)
							for (int j = 0; j < 7; j++)
							{
								place[i][j].in = 0;//clear the int array to begain with empty board
								place[i][j].player = ' ';//clear the char array to begain with empty board
							}
							board->draw();//draw the board

						}

					}
				}
				 
				continue;
			}
		if (number_of_coin == 42 && winner == false)
		{
			switch (csdl_setup->GetMainEvent()->type)
			{
			case SDL_KEYDOWN:
				switch (csdl_setup->GetMainEvent()->key.keysym.sym)
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
					board->draw();//draw the board
				
				
				}
			}
			continue;
		}


			//moving with keyboard
			switch (csdl_setup->GetMainEvent()->type)
			{
			case SDL_KEYDOWN:
				switch (csdl_setup->GetMainEvent()->key.keysym.sym)
				{
				case SDLK_a:
					if (number_of_coin % 2 == 0)//RED COIN "even number" and don't move out the board
						red_coin->SetX(red_coin->GetX() - 100);//MOVE THE RED COIN -100 WHEN PRESS <--
					if (number_of_coin % 2 != 0)//YELLOW COIN "odd number" and don't move out the board
						yellow_coin->SetX(yellow_coin->GetX() - 100);//MOVE THE YELLOW COIN -100 WHEN PRESS <--

					break;
				case SDLK_d:
					if (number_of_coin % 2 == 0)//RED COIN "even number" and don't move out the board
						red_coin->SetX(red_coin->GetX() + 100);//MOVE THE RED COIN -100 WHEN PRESS <--
					if (number_of_coin % 2 != 0)//YELLOW COIN "odd number" and don't move out the board
						yellow_coin->SetX(yellow_coin->GetX() + 100);//MOVE THE YELLOW COIN -100 WHEN PRESS <--

					break;
				case SDLK_SPACE:
					if (number_of_coin % 2 == 0 && winner == false)
					{
						if (red_coin->GetY() >= 10)
						{
							int COL = (red_coin->GetX() - 8) / 100;
							int ROW = drop(COL);
							if (ROW != 1)
							{
								place[ROW - 2][(red_coin->GetX() - 8) / 100].player = 'A';
								red_coin->SetY(red_coin->GetY() + (66 * ROW));
								red_coin->SetY(red_coin->GetY() - ((6 - ROW) * 13));
								Rect1.push_back(red_coin->GetRect());//push the coin in the vector
								//draw the yellow coin after the red coin drop
								yellow_coin = new CSprite(csdl_setup->GetRenderer(), "player 2.png", 8, 10, 96, 86);
								yellow_coin->draw();

							}
							else
							{
								break;//if drop in illegal place will break
							}
							winner = check(ROW - 2, COL);//check the winner
							if (winner == true)
							{  //load the winner picture
								red_win->draw();
								
								break;
							}
						}

					}
					else if (number_of_coin % 2 != 0)
					{
						if (yellow_coin->GetY() >= 10)
						{
							int COL = (yellow_coin->GetX() - 8) / 100;
							int ROW = drop(COL);
							if (ROW != 1)
							{
								place[ROW - 2][(yellow_coin->GetX() - 8) / 100].player = 'B';
								yellow_coin->SetY(yellow_coin->GetY() + (66 * ROW));
								yellow_coin->SetY(yellow_coin->GetY() - ((6 - ROW) * 13));
								Rect2.push_back(yellow_coin->GetRect());//push the coin in the vector
								//draw the yellow coin after the red coin drop
								red_coin = new CSprite(csdl_setup->GetRenderer(), "player 1.png", 8, 10, 96, 86);
								red_coin->draw();

							}
							else
							{
								break;//if drop in illegal place will break
							}
							winner = check(ROW - 2, COL);//check the winner
							if (winner == true)
							{  //load the winner picture
								yellow_win->draw();
								break;
							}

						}
					}
					if (!winner)
						number_of_coin++;
					break;

				default:
					break;
				}
				break;
			default:
				break;
			}
			

			csdl_setup->end();
		}
	}

