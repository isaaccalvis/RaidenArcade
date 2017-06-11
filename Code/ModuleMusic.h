#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__
#include "Module.h"
#include "Application.h"
#include "SDL_mixer\include\SDL_mixer.h"

class ModuleMusic : public Module {
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	bool CleanUp();

	bool LoadMusic(const char* musicName);
	bool UnloadMusic();

	uint LoadFX(const char* path);
	bool PlayFX(uint FXname);
	bool UnloadFX(uint FXname);

private:
	Mix_Music* music = nullptr;
	Mix_Chunk* fx[500];
	uint ret = 0;
	uint last_fx = 1;
};

#endif