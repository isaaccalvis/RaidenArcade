#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleBackground : public Module {
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	iPoint PosCow1, PosCow2, PosCow3, PosCow4, PosCow5, PosCow6;
	iPoint PosCowboys;

	SDL_Texture* cows = nullptr;
	Animation cow1, cow2, cow3, cow4, cow5, cow6;
	Animation cowboys;
	
	float posBackGround;
	float speedBackGround;
	int controlador_spawn_LightShooter;
	int controlador_spawn_BonusPlane;
	int controlador_spawn_box;
	int controlador_spawn_Turret;

};

#endif