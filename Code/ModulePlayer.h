#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	
private:
	int current_time;
public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect PROTA;
	Collider* colPlayer1;
	bool destroyed = false;
	bool potMoure;
	bool GodMode = false;
	uint videsP1;
	uint puntuacioP1;
	Animation* current_animation = nullptr;
	Animation idle;	
	Animation rightMov;
	Animation rightMov2;
	Animation leftMov;
	Animation leftMov2;
	Animation pDamaged;
	Animation pDead;
	Animation Despegar1;
	Animation Despegar2;
	Animation Despegar3;

	int font_score = -1;
	char score_text[10];
	int auxiliar_vida = 0;
};

#endif