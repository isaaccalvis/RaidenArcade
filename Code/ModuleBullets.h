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
	// Player 1

	PowerUpType powerUpTypePlayer1 = Vulkan;
	MissileUpType missileUpTypePlayer1 = Nuclear; // comença al nivell 0 així que dona igual
	
	int powerUpLevelPlayer1;
	int missileUpLevelPlayer1;
	int esperaShootP1;
	int esperaMissileP1;
	int postXYbomb[4] = { 0,0,0, 0 }; // 0 = x, 1 = y, 3 = tempsEsperaSeguentBomba, 4 = copsQueFaMal
	int bombsPlayer1;
	bool bombOnPlayer1 = false;

	int current_timeP1;

	// Player 2

	PowerUpType powerUpTypePlayer2 = Vulkan;
	MissileUpType missileUpTypePlayer2 = Nuclear; // comença al nivell 0 així que dona igual

	int powerUpLevelPlayer2;
	int missileUpLevelPlayer2;
	int esperaShootP2;
	int esperaMissileP2;
	int postXYbombP2[4] = { 0,0,0, 0 };
	int bombsPlayer2;
	bool bombOnPlayer2 = false;

	int current_timeP2;


	int quiDisparaHoaming; // si es 1, el dispara el player1, si es 2, el dispara el player 2
	// Desfase
	int desfaseSpriteDispar; // Serveix per restar la mitat de W del sprite de la bala, aixi surt centrat
};
#endif
