#pragma once
class CSDL_Setup
{
	public:
		CSDL_Setup(bool *quit, int ScreenWidth, int ScreenHeight);
		~CSDL_Setup();
		SDL_Renderer* GetRenderer();
		SDL_Event* GetMainEvent();
		void begain();
		void end();
	    int	ScreenWidth = 1073;
		int ScreenHeight = 571;
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event* mainEvent;
};

