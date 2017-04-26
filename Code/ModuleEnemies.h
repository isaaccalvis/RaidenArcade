#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#define MAX_ENEMIES 500

enum ENEMY_TYPES{
	NO_TYPE,
	LIGHT_SHOOTER,
	BASIC_TANK,
	BONUS_PLANE,
	TURRET,
	// --- OBJECTS ---
	BOX,
	MEDAL,
	POWER_UP
};

class Enemy;

struct EnemyInfo{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class ModuleEnemies : public Module{
public:
	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y);
	SDL_Texture* sprite_LightShooter;
	SDL_Texture* sprite_BasicTank;
	SDL_Texture* sprite_Turret;
	SDL_Texture* sprite_BonusPlane;
	SDL_Texture* sprite_Box;
	SDL_Texture* sprite_Medal_PowerUp_Bonus;



private:
	void SpawnEnemy(const EnemyInfo& info);

private:
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];


};

#endif