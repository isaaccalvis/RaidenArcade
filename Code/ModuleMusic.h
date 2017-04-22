#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__
#include "Module.h"
#include "Application.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_MUSIC 8
#define MAX_FX 10

enum nombreMusica {
	MUSICA_NIVEL_1,
	MUSICA_NIVEL_2,
	MUSICA_NIVEL_3,
	MUSICA_GAME_OVER,
	MUSICA_GAME_CONTINUE,
	MUSICA_STAGE_CLEAR
};
enum nombreFX {
	FX_DISPARAR,
	FX_INTRODUCIR_MONEDA
};

class ModuleMusic : public Module {
public:
	ModuleMusic();
	~ModuleMusic();

	bool Init();
	update_status Update();
	bool CleanUp();
	
	bool CargarMusica(nombreMusica nombreMusica);
	bool DescargarMusica(nombreMusica nombreMusica);
	bool CargarFX(nombreFX nombreFX);
	bool DescargarFX(nombreFX nombreFX);

public:
	Mix_Music* MUSIC_IN_EXECUTION[MAX_MUSIC];
	Mix_Chunk* FX_IN_EXECUTION[MAX_FX];
};

#endif