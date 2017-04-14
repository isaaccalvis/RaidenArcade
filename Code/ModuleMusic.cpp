#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleMusic.h"

ModuleMusic::ModuleMusic() {}
ModuleMusic::~ModuleMusic() {}

bool ModuleMusic::Init() {
	bool ret = true;
	Mix_Init(MIX_INIT_OGG);

	for (int i = 0; i < MAX_MUSIC; i++)
		MUSIC_IN_EXECUTION[i] = nullptr;
	for (int i = 0; i < MAX_FX; i++)
		FX_IN_EXECUTION[i] = nullptr;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	if (Mix_Init(MIX_INIT_OGG) < 0) {
		LOG("Music Module can't Load");
		ret = false;
	}
	return ret;
}

update_status ModuleMusic::Update() {
	return UPDATE_CONTINUE;
}

bool ModuleMusic::CleanUp() {
	bool ret = true;
	for (int i = 0; i < MAX_MUSIC; i++)
		Mix_FreeMusic(MUSIC_IN_EXECUTION[i]);
	for (int i = 0; i < MAX_FX; i++)
		Mix_FreeChunk(FX_IN_EXECUTION[i]);
	
	return ret;
}

bool ModuleMusic::CargarMusica(nombreMusica nombreMusica) {
	bool ret = true;
	switch (nombreMusica) {
	case MUSICA_NIVEL_1:
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
bool ModuleMusic::CargarFX(nombreFX nombreFX) {
	switch (nombreFX) {
	case FX_DISPARAR:
		FX_IN_EXECUTION[nombreFX] = Mix_LoadWAV("Audio/Fx/Shot_1(bullet).wav");
		Mix_PlayChannel(0, FX_IN_EXECUTION[nombreFX], 0);
		break;
	case FX_INTRODUCIR_MONEDA:

		break;
	}
	return true;
}
bool ModuleMusic::DescargarMusica(nombreMusica nombreMusica) {
	switch (nombreMusica) {
	case MUSICA_NIVEL_1:
		MUSIC_IN_EXECUTION[nombreMusica] = Mix_LoadMUS("Audio/Music/Stage_1-4.ogg");
		Mix_FreeMusic( MUSIC_IN_EXECUTION[nombreMusica] );
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
bool ModuleMusic::DescargarFX(nombreFX nombreFX) {
	switch (nombreFX) {
	case FX_DISPARAR:
		FX_IN_EXECUTION[nombreFX] = Mix_LoadWAV("Audio/Fx/Shot_1(bullet).wav");
		Mix_FreeChunk(FX_IN_EXECUTION[nombreFX]);
		FX_IN_EXECUTION[nombreFX] = NULL;
		break;
	case FX_INTRODUCIR_MONEDA:

		break;
	}	
	return true;
}