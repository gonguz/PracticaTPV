#include "JuegoPG.h"
#include "SDL.h"
#include <iostream>

int const HEIGHT = 500;
int const WIDTH = 500;

JuegoPG::JuegoPG()
{
	initSDL(pWin, pRender);
	if (!initSDL(pWin, pRender)) {
		error = true;
		pWin = nullptr;
		pRender = nullptr;
		cout << "Ha habido un error, ERROR \n";
	}
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 0;

	puntos = 0;

	error = false;
	gameOver = false;
	exit = false;
}


JuegoPG::~JuegoPG()
{
}

void JuegoPG::run() {
	if (!error) {
		Uint32 MSxUpdate = 500;
		cout << "PLAY \n";
		Uint32 lastUpdate = SDL_GetTicks();
		render();
		handle_events();
		while (!exit && !gameOver) {
			if (SDL_GetTicks() - lastUpdate >= MSxUpdate){ //while(elapsed >= MSxUpdate)
				update();
				lastUpdate = SDL_GetTicks();
			}
			render();
			handle_events();
		}
		if (exit) cout << "EXIT \n";
		else
		{
			render();
			cout << "Has obtenido " << puntos << "puntos \n";
		}
		SDL_Delay(1000);
		cin.get();
	}
}

bool JuegoPG::initSDL(SDL_Window* &pWin, SDL_Renderer* &pRender) {
	bool success = true; 

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL could not initialize! \nSDL_Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else {
		//Create window: SDL_CreateWindow("SDL Hello World", posX, posY, width, height, SDL_WINDOW_SHOWN);
		pWin = SDL_CreateWindow("SDL Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (pWin == nullptr) {
			cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else {
			//Get window surface:
			pRender = SDL_CreateRenderer(pWin, -1, SDL_RENDERER_ACCELERATED);
			//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255); //Set background color to black 
			if (pRender == nullptr) {
				cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
				success = false;
			}
		}
	}

	return success;
}

void JuegoPG::closeSDL(SDL_Window* &pWin, SDL_Renderer* &pRender) {
	SDL_DestroyRenderer(pRender);
	pRender = nullptr;

	SDL_DestroyWindow(pWin);
	pWin = nullptr;

	SDL_Quit();
}

bool JuegoPG::initGlobos() {
	bool succes = true;
	textures[0] = new TexturasSDL();
	textures[0]->load(pRender, "Balloon.png");
	textures[1] = new TexturasSDL();
	textures[1]->load(pRender, "background.png");
	rect = new SDL_Rect();
	rect->h = HEIGHT;
	rect->w = WIDTH;
	rect->x = 0;
	rect->y = 0;
 	for (int i = 0; i < globos.size(); i++)
		globos.emplace_back(new GlobosPG(textures[0], rand() % 500, rand() % 500));
	return succes;
}

void JuegoPG::freeGlobos(vector<GlobosPG*> globos) {
	for (size_t i = 0; i < globos.size(); ++i) {
		globos[i] = nullptr;
	} 
	textures[0] = nullptr;
	textures[1] = nullptr;
}

void JuegoPG::render() const {
	SDL_RenderClear(pRender);
	textures[1]->draw(pRender,rect);
}

void JuegoPG:: onClick(int pmx, int pmy) {
	int auxPunt;
	for (size_t i = 0; i < globos.size(); ++i) {
		globos[i]->onClick(pmx, pmy, auxPunt);
		puntos += auxPunt;
	}
}

void JuegoPG:: update() {
	for (size_t i = 0; i < globos.size(); ++i) {
		globos[i]->update();
	}
}

bool JuegoPG::handle_events() {
	SDL_Event e;
	bool running = true;
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			exit = true;
			closeSDL(pWin, pRender);
			running = false;
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				cout << "CLICK";
				onClick(e.button.x, e.button.y);
			}
		}   // ...
	}
	return !running;
}


