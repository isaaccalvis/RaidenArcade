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
	void OnCollision(Collider* c1, Collider* c2);

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect PROTA2;
	Collider* colPlayer2;
	bool destroyed = false;
	bool jugador2Activat;
	int puntuacioP2;
	int videsP2;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation rightMov;
	Animation leftMov;
};

#endif