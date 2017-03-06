#include <stdlib.h>
#include <iostream>
#include "include\SDL.h"
#pragma comment (lib, "lib/x86/SDL2.lib")
#pragma comment (lib, "lib/x86/SDL2main.lib")

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

SDL_Rect cuadrat = { 0, 0, 60, 60 };
SDL_Event tecla;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	g_pWindow = SDL_CreateWindow("Finestra1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
	int ingame = 0;
	while (ingame == 0) {
		while (SDL_PollEvent(&tecla)) {
			switch (tecla.key.keysym.sym) {
			case SDLK_UP:
				if (cuadrat.y > 0)
					cuadrat.y = cuadrat.y - 20;
				else
					cuadrat.y = 0;
				break;
			case SDLK_DOWN:
				if (cuadrat.y < 480 - cuadrat.h)
					cuadrat.y = cuadrat.y + 20;
				else
					cuadrat.y = 480 - cuadrat.h;
				break;
			case SDLK_RIGHT:
				if (cuadrat.x < 640 - cuadrat.w)
					cuadrat.x = cuadrat.x + 20;
				else
					cuadrat.x = 640 - cuadrat.w;
				break;
			case SDLK_LEFT:
				if (cuadrat.x > 0)
					cuadrat.x = cuadrat.x - 20;
				else
					cuadrat.x = 0;
				break;
			// Increment i decrement de tamany
			case SDLK_q:
				cuadrat.w = cuadrat.w + 5;
				break;
			case SDLK_a:
				cuadrat.w = cuadrat.w - 5;
				break;
			case SDLK_w:
				cuadrat.h = cuadrat.h + 5;
				break;
			case SDLK_s:
				cuadrat.h = cuadrat.h - 5;
				break;
			// Per acabar execucio
			case SDLK_p:
				ingame = 1;
				break;
			}
		}

		SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 0);
		SDL_RenderClear(g_pRenderer);

		SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 0, 0);
		SDL_RenderFillRect(g_pRenderer, &cuadrat);
		SDL_RenderPresent(g_pRenderer);

		std::cout << "coor x: "<<cuadrat.x << "\t coor y: " << cuadrat.y << std::endl;
	}

	SDL_Delay(1000);
	SDL_Quit();

	return 0;
}