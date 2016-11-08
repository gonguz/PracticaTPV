#pragma once
#include "SDL.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class TexturasSDL
{
public:
	TexturasSDL();
	~TexturasSDL();
	bool load(SDL_Renderer* pRender, string const& nomArchivo);
	void draw(SDL_Renderer* pRender, SDL_Rect const& rect);

private: 
	SDL_Texture* pText;
	struct Tam
	{
		int alto;
		int ancho;
	}t;
};

