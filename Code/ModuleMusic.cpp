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

bool ModuleMusic::LoadMusic(MusicName nombreMusica) {
	bool ret = true;
	switch (nombreMusica) {
	case MUSIC_LEVEL_1:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Stage_1-4.ogg");
		Mix_PlayMusic(MUSIC_IN_EXECUTION[nombreMusica], -1);
		break;
	case MUSICA_NIVEL_2:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Stage_2-7.ogg");
		Mix_PlayMusic(MUSIC_IN_EXECUTION[nombreMusica], -1);
		break;
	case MUSICA_GAME_CONTINUE:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Continue.ogg");
		Mix_PlayMusic(MUSIC_IN_EXECUTION[nombreMusica], -1);
		break;
	}
	return ret;
}

bool ModuleMusic::UnloadMusic(MusicName nombreMusica) {
	switch (nombreMusica) {
	case MUSIC_LEVEL_1:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Stage_1-4.ogg");
		Mix_FreeMusic(MUSIC_IN_EXECUTION[nombreMusica]);
		MUSIC_IN_EXECUTION[nombreMusica] = NULL;
		break;
	case MUSICA_NIVEL_2:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Stage_2-7.ogg");
		Mix_FreeMusic(MUSIC_IN_EXECUTION[nombreMusica]);
		MUSIC_IN_EXECUTION[nombreMusica] = NULL;
		break;
	}
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
			ret = last_fx;
		}
		last_fx++;
	
	return ret;
}

bool ModuleMusic::PlayFX(uint FXname) {
	
		Mix_PlayChannel(0, fx[FXname], 0);
	
	return true;
}

//bool ModuleMusic::UnloadFX(uint nombreFX) {
//	bool ret = false;
//
//			if (fx[nombreFX] != nullptr) {
//
//				Mix_FreeChunk(fx[nombreFX]);
//				fx[nombreFX] = nullptr;
//				ret = true;
//				last_fx--;
//			}
//	return true;
//}