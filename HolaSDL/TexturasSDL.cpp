#include "TexturasSDL.h"
#include "SDL.h"
#include <iostream>
using namespace std;


TexturasSDL::TexturasSDL()
{
	pText = nullptr;
	t.alto = 0;
	t.ancho = 0;
}


TexturasSDL::~TexturasSDL()
{
}

bool TexturasSDL::load(SDL_Renderer* pRender,string const nomArchivo) {
	SDL_Surface* pTempSurface = nullptr;
	bool success = true;

	pTempSurface = SDL_LoadBMP(nomArchivo.c_str());  // si usamos string: bmpName.c_str() 
	if (pTempSurface == nullptr) {
		cout << "Unable to load image " << nomArchivo << "! \nSDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		pText = SDL_CreateTextureFromSurface(pRender, pTempSurface);
		t.alto = pTempSurface->clip_rect.h;
		t.ancho = pTempSurface->clip_rect.w;
		SDL_FreeSurface(pTempSurface);
		success = pText != nullptr;
	}

	return success;
}

void TexturasSDL::draw(SDL_Renderer* pRender, SDL_Rect const& rect) {
	SDL_RenderCopy(pRender, pText, nullptr, &rect);
}
