#include <stdlib.h>
#include <iostream>
#include "include\SDL.h"
#pragma comment (lib, "lib/x86/SDL2.lib")
#pragma comment (lib, "lib/x86/SDL2main.lib")

#define WINDOW_AMPLADA 640
#define WINDOW_LLARGADA 480
#define NUMERO_BALES 2

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
SDL_Surface* texturaCarregant;
SDL_Texture* img_Nau;

SDL_Rect PROTA = { 0, 0, 60, 60 };
SDL_Rect DISPAR[2] = { 0, 0, 10, 10 };
SDL_Event TECLA;

int ingame = 0, moventUp = 0, moveRight = 0, numBala = 0;

void InicialitzacionsVaries();
void Renders();
void PolliMoviments();
void shoot(int numBala);

int main(int argc, char* argv[]) {
	InicialitzacionsVaries();
	while (ingame == 0) {
		PolliMoviments();
		Renders();
		SDL_Delay(2);
	}
	SDL_Quit();
	return 0;
}

void InicialitzacionsVaries() {
	SDL_Init(SDL_INIT_EVERYTHING);
	g_pWindow = SDL_CreateWindow("Finestra1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_AMPLADA, WINDOW_LLARGADA, SDL_WINDOW_SHOWN);
	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);

	DISPAR[1] = DISPAR[0];
	// Render de Imagetes BMP
	texturaCarregant = SDL_LoadBMP("nau.bmp");
	img_Nau = SDL_CreateTextureFromSurface(g_pRenderer, texturaCarregant);
	SDL_FreeSurface(texturaCarregant);
}
void shoot(int numBala) {
	DISPAR[numBala].x = PROTA.x + (PROTA.w / 2) - DISPAR[numBala].w;
	DISPAR[numBala].y = PROTA.y;
}
void Renders() {
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 0);
	SDL_RenderClear(g_pRenderer);
	for (int i = 0; i < NUMERO_BALES; i++) {
		SDL_SetRenderDrawColor(g_pRenderer, 0, 255, 0, 0);
		SDL_RenderFillRect(g_pRenderer, &DISPAR[i]);
	}
	SDL_RenderCopy(g_pRenderer, img_Nau, NULL, &PROTA);	// Imatge de la Nau Prota

	SDL_RenderPresent(g_pRenderer);
}
void PolliMoviments() {
	// Crida de tecles
	while (SDL_PollEvent(&TECLA)) {
		if (TECLA.type == SDL_KEYDOWN && TECLA.key.repeat == 0) {
			switch (TECLA.key.keysym.sym) {
			case SDLK_UP: moventUp = 1; break;
			case SDLK_DOWN: moventUp = -1; break;
			case SDLK_RIGHT: moveRight = 1; break;
			case SDLK_LEFT: moveRight = -1; break;
			case SDLK_p: ingame = 1; break; // Sortir del ingame
			}
		}
		if (TECLA.type == SDL_KEYUP && TECLA.key.repeat == 0) {
			switch (TECLA.key.keysym.sym) {
			case SDLK_UP: moventUp = 0; break;
			case SDLK_DOWN: moventUp = 0; break;
			case SDLK_RIGHT: moveRight = 0; break;
			case SDLK_LEFT: moveRight = 0; break;
			}
		}
		if (TECLA.key.repeat == 0 && TECLA.type == SDL_KEYUP) {
			switch (TECLA.key.keysym.sym) {
			case SDLK_SPACE:
				numBala++;
				if (numBala >= NUMERO_BALES)
					numBala = 0;
				shoot(numBala);
				break;
			}
		}
	}

	// Moviments
	if (moventUp == 1)
		if (PROTA.y > 0)
			PROTA.y--;
		else
			PROTA.y = 0;
	else if (moventUp == -1)
		if (PROTA.y < WINDOW_LLARGADA - PROTA.h)
			PROTA.y++;
		else
			PROTA.y = WINDOW_LLARGADA - PROTA.h;

	if (moveRight == 1)
		if (PROTA.x < WINDOW_AMPLADA - PROTA.w)
			PROTA.x++;
		else
			PROTA.x = WINDOW_AMPLADA - PROTA.w;
	else if (moveRight == -1)
		if (PROTA.x > 0)
			PROTA.x--;
		else
			PROTA.x = 0;
	// Moviments Bales
	for (int i = 0; i < NUMERO_BALES; i++)
		DISPAR[i].y -= 5;
}