#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module(){
	for(uint i = 0; i < MAX_TEXTURES; ++i)
		textures[i] = nullptr;
}

ModuleTextures::~ModuleTextures(){}

bool ModuleTextures::Init(){
	LOG("Init Image library");
	bool ret = true;

	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags){
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTextures::CleanUp(){
	LOG("Freeing textures and Image library");
	bool ret = true;
	for(uint i = 0; i < MAX_TEXTURES; ++i)
		if(textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);

	IMG_Quit();
	return ret;
}

SDL_Texture* const ModuleTextures::Load(const char* path){
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == NULL){
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}else{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

		if(texture == NULL){
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}else{
			textures[last_texture++] = texture;
		}
		SDL_FreeSurface(surface);
	}

	return texture;
}


bool ModuleTextures::Unload(SDL_Texture* texture){
	bool ret = false;

	for (uint i = 0; i < MAX_TEXTURES; ++i)
	{
		if (texture == textures[i])
		{
			SDL_DestroyTexture(textures[i]);
			textures[i] = nullptr;
			ret = true;
			break;
		}
	}
	return ret;
}