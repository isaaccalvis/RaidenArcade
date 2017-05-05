#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleMusic.h"
#include "SDL\include\SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleMusic::ModuleMusic() {}
ModuleMusic::~ModuleMusic() {}

bool ModuleMusic::Init() {
	bool ret = true;

	SDL_Init(0);
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_OGG);	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	return ret;
}

bool ModuleMusic::CleanUp() {
	bool ret = true;
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	
	return ret;
}

bool ModuleMusic::LoadMusic(const char* path) {
	bool ret = true;
	
	music = Mix_LoadMUS(path);
	Mix_PlayMusic(music, -1);

	return ret;
}

bool ModuleMusic::UnloadMusic() {
	Mix_FreeMusic(music);
	music = nullptr;
	Mix_HaltMusic();
	return true;
}

uint ModuleMusic::LoadFX(const char* path) {

	uint ret = 0;
	Mix_Chunk* audio = Mix_LoadWAV(path);

		if (audio == nullptr) {
			LOG("Cannot load WAV.")
		}
		else {
			fx[last_fx] = audio;
			ret = last_fx++;
			if (last_fx == 500) {
				last_fx = 0;
				ret = last_fx;
			}
		}
	
	return ret;
}

bool ModuleMusic::PlayFX(uint FXname) {
	
	if (fx[FXname] != nullptr) {
		Mix_PlayChannel(0, fx[FXname], 0);
		ret = true;
	}
	return true;
}

bool ModuleMusic::UnloadFX(uint nombreFX) {
	bool ret = false;

			if (fx[nombreFX] != nullptr) {

				Mix_FreeChunk(fx[nombreFX]);
				fx[nombreFX] = nullptr;
				ret = true;
				last_fx--;
			}
	return true;
}