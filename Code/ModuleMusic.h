#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__
#include "Module.h"
#include "Application.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_MUSIC 8
#define MAX_FX 10

// Enum que no se com implemetar
/*
enum MUSIC_NAME {
	MUSIC_LV1 = 1,
	MUSIC_LV2,
	MUSIC_LV3,
	MUSIC_LV4,
	MUSIC_LV5,
	MUSIC_LV6,
	MUSIC_LV7,
	MUSIC_LV8,
	MUSIC_CONTINUE,
	MUSIC_GAME_OVER
};
*/

class ModuleMusic : public Module {
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	update_status Update();
	bool CleanUp();
	
public:
	Mix_Music* MUSIC_IN_EXECUTION[MAX_MUSIC];
	Mix_Chunk* FX_IN_EXECUTION[MAX_FX];
};

#endif