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
	MUSIC_IN_EXECUTION[0] = Mix_LoadMUS("Audio/Music/Stage_1-4.ogg");
	FX_IN_EXECUTION[0] = Mix_LoadWAV("Audio/Fx/Shot 1(bullet).wav");

	Mix_PlayMusic(MUSIC_IN_EXECUTION[0], -1);

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