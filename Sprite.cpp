#include "stdafx.h"
#include "Sprite.h"


CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h)
{
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "couldn't load " << FilePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;

}


CSprite::~CSprite()
{
	SDL_DestroyTexture(image);
}


void CSprite::draw()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
}

void CSprite::SetX(int X)
{
	rect.x = X;
}

void CSprite::SetY(int Y)
{
		rect.y = Y;
}

void CSprite::SetPosition(int X,int Y)
{
	rect.x = X;
	rect.y = Y;
}

int  CSprite::GetX()
{
	return rect.x;
}

int  CSprite::GetY()
{
	return rect.y;
}

//void CSprite::GetRect(int &x,int &y,int &w,int &h)
//{
//	rect.x = x;
//	rect.y = y;
//	rect.w = w;
//	rect.h = h;
//}


