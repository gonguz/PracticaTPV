#pragma once
#include "SDL.h"
#include "TexturasSDL.h"
#include "GlobosPG.h"

class GlobosPG
{
public:
	GlobosPG( TexturasSDL* img, int px, int py);
	~GlobosPG();
	void draw(SDL_Renderer* pRender);
	bool onClick(int pmx, int pmy, int & auxPuntos);
	bool update();

private:
	TexturasSDL * pText;
	int puntos;
	struct Posicion {
		int posX;
		int posY;
	};
	Posicion * p;

	struct Tamaño 
	{
		int alto;
		int ancho;
	}t;

	SDL_Rect* pRect;

	bool explotado, visible;

	static const int PVIS = 70;
	static const int PDES = 30;
	static const int DT = 5;
	static const int AP = 5;
};

