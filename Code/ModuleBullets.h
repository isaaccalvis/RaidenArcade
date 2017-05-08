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
	NONE = 0,
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
	PowerUpType powerUpTypePlayer1 = Vulkan;
	MissileUpType missileUpTypePlayer1 = NONE;
	int bombsPlayer1;
	bool bombOnPlayer1 = false;

	int powerUpLevelPlayer2;
	int current_time;

};
#endif
