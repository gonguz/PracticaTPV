#pragma once
#include "SDL.h"
#include "TexturasSDL.h"
#include "globosPG.h"
#include <vector>
using namespace std;


class JuegoPG
{
public:

	JuegoPG();
	~JuegoPG();
	void run();


private:
	SDL_Window * pWin;
	SDL_Renderer * pRender;
	SDL_Rect* rect;
	SDL_Color color;
	vector<GlobosPG*> globos;
	vector<TexturasSDL*> textures;
	int puntos;
	bool error, exit, gameOver;
	bool initSDL(SDL_Window* &pWin, SDL_Renderer* &pRender);
	void closeSDL(SDL_Window* &pWin, SDL_Renderer* &pRender);
	bool initGlobos();
	void freeGlobos(vector <GlobosPG*> globos);
	void render()const;
	void onClick(int pmx, int pmy);
	void update();
	bool handle_events();
};

