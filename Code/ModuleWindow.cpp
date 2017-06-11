#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"

ModuleWindow::ModuleWindow() : Module(){}

ModuleWindow::~ModuleWindow(){}

bool ModuleWindow::Init(){
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		LOG("SDL_VIDEO could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
		ret = false;
	}else{
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if(WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if(WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if(WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if(WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ORIGINAL_CAMERA_WEIGHT, ORIGINAL_CAMERA_HEIGHT, flags);

		if(window == NULL){
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}else{
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp(){
	LOG("Destroying SDL window and quitting all SDL systems");
	bool ret = true;
	if(window != NULL)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return ret;
}