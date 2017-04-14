#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module {
public:
	ModulePlayer2();
	~ModulePlayer2();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation rightMov;
	Animation leftMov;
	SDL_Rect PROTA2;
	bool jugador2Activat = false;
};
#endif