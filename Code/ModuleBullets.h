#ifndef __ModuleBullets_H__
#define __ModuleBullets_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleParticles.h"
enum PowerUpType {
	Vulkan = 0,
	Laser
};
enum MissileUpType {
	Nuclear,
	Hoaming
};
class ModuleBullets : public Module {
public:
	ModuleBullets();
	~ModuleBullets();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();

public:
	int powerUpLevelPlayer1;
	int missileUpLevelPlayer1;
	PowerUpType powerUpTypePlayer1 = Vulkan;
	MissileUpType missileUpTypePlayer1 = Nuclear; // comença al nivell 0 així que dona igual
	int bombsPlayer1;
	bool bombOnPlayer1 = false;
	int esperaShootP1 = 0;
	int esperaMissileP1;
	int postXYbomb[4] = { 0,0,0, 0 }; // 0 = x, 1 = y, 3 = tempsEsperaSeguentBomba, 4 = copsQueFaMal

	int powerUpLevelPlayer2;
	int current_time;

	int desfaseSpriteDispar; // Serveix per restar la mitat de W del sprite de la bala, aixi surt centrat
};
#endif
