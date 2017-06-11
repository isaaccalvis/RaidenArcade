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

	void CridaScoreGeneral();
private:
	int current_time;
	float posShipIncial;
public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;

	float posBackGround;
	float speedBackGround;
	int controlador_spawn_LightShooter;
	int controlador_spawn_BonusPlane;
	int controlador_spawn_box;
	int controlador_spawn_vTank;
	int controlador_spawn_Turret;
	int currenTime_Asteroids;
	int controlador_spawn_Heavy_Turret;
	int controlador_spawn_Basic_Tank;
	int controlador_spawn_Light_Shooter_Lateral;
	int controlador_spawn_Diamond_Plane;
	int controlador_spawn_Heavy_Orange_Airship;
	int auxiliar_musica_boss;
	int current_time_boss;
	int contadorAuxiliarBoss;

	int posScoreX;

	bool controlador_Auxiliar_Background_1 = true; // aixo serveix perk els players no es posin en potMoure = true sempre;
};

#endif