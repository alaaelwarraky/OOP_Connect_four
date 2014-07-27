#include "stdafx.h"
#include "SDL_Setup.h"

//constructor
CSDL_Setup::CSDL_Setup(bool *quit,int ScreenWidth ,int ScreenHeight)
{
	ScreenWidth = 1073;
	ScreenHeight = 571;
	window = NULL;
	window = SDL_CreateWindow(" CONNECT FOUR ", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		std::cout << "window couldn't be created " << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
}

//destructor
CSDL_Setup::~CSDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}
//function in class ->> get renderer cuz it's private
SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}
//function in class ->> get mainEvent cuz it's private
SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}
//thats begain GAME LOOP
void CSDL_Setup::begain()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);

}
//thats end GAME LOOP
void CSDL_Setup::end()
{
	SDL_RenderPresent(renderer);
}
