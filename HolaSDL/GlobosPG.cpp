#include "GlobosPG.h"
#include "SDL.h"
#include <iostream>
using namespace std;



GlobosPG::GlobosPG(TexturasSDL* img, int px, int py)
{
	pText = img;
	p = new Posicion{ px, py };
	pRect->x = 0;
	pRect->y = 0;
	pRect->w = 420;
	pRect->h = 360;
	explotado = false;
	visible = false;
	puntos = 1;
}


GlobosPG::~GlobosPG()
{
}

void GlobosPG::draw(SDL_Renderer* pRender) {
	if (visible) {
		pText->draw(pRender, *pRect);
	}
}

bool GlobosPG::onClick(int pmx, int pmy, int & auxPuntos) {
	auxPuntos = 0;
	if (visible) {
		if (pmx >= p->posX && pmx <= pRect->w*p->posX && pmy >= p->posY && pmy <= pRect->h*p->posY) {
			auxPuntos = puntos;
			update();
		}
		return explotado;
	}
	else
		return explotado;
}
bool GlobosPG::update() {

	if (rand() % 100 < PVIS) visible = true;  else visible = false;

	if (visible) {

		if (rand() % 100 < PDES) {
			t.alto -= DT;
			t.ancho -= DT;
			puntos += AP;
		}

		if (t.alto <= 0)
			explotado = true;

		return explotado;
	}
	return visible;
}
