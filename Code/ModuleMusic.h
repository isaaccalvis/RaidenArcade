#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__
#include "Module.h"
#include "Application.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define MAX_MUSIC 10
#define MAX_FX 500

enum MusicName {
	MUSIC_LEVEL_1,
	MUSICA_NIVEL_2,
	MUSICA_NIVEL_3,
	MUSICA_GAME_OVER,
	MUSICA_GAME_CONTINUE,
	MUSICA_STAGE_CLEAR
};

class ModuleMusic : public Module {
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	bool CleanUp();

	bool LoadMusic(MusicName musicName);
	bool UnloadMusic(MusicName musicName);

	uint LoadFX(const char* path);
	bool PlayFX(uint FXname);
	bool UnloadFX(uint FXname);

private:

	Mix_Music* MUSIC_IN_EXECUTION[MAX_MUSIC];
	Mix_Chunk* fx[500];
	uint ret = 0;
	uint last_fx = 1;
};

#endif