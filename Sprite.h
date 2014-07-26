#pragma once
class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer,std::string FilePath, int x,int y,int w,int h);
	~CSprite();
	void draw();

	void SetX(int X);
	void SetY(int Y);
	void SetPosition(int X, int Y);

	//void GetRect(int &x, int &y, int &w, int &h);
	int GetX();
	int GetY();
private:
	SDL_Texture* image;
	SDL_Rect rect;
	SDL_Rect crop;
	int img_width;
	int img_height;
	SDL_Renderer* renderer;
};

