#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "p2Point.h"

#define MAX_ENEMIES 600

enum ENEMY_TYPES{
	NO_TYPE,
	LIGHT_SHOOTER,
	BASIC_TANK,
	BONUS_PLANE,
	TURRET,
	BOMB,
	ASTEROID,
	DIAMOND_PLANE,
	HEAVY_ORANGE_AIRSHIP,
	HEAVY_TURRET,
	LIGHT_SHOOTER_LATERAL,
	VTANK,
	BASIC_TANK_DESTROY,
	HEAVY_TURRET_DESTROY,
	// --- OBJECTS ---
	BOX,
	MEDAL,
	POWER_UP,
	MISSILE_UP,
	// --- HOAMING ---
	HOAMING_MISSILE,
	// --- BOSS ---
	BOSS6_HEAD,
	BOSS6_BASE
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
	SDL_Texture* sprite_Asteroid;
	SDL_Texture* sprite_Diamond_Plane;
	SDL_Texture* sprite_Heavy_Orange_Airship;
	SDL_Texture* sprite_Heavy_Turret;
	SDL_Texture* sprite_Light_Shooter_Lateral;
	SDL_Texture* sprite_vTank;
	SDL_Texture* sprite_boss6;
	SDL_Texture* sprite_enemyBomb;

	uint hit;
	uint Bonus;
	uint box;
	uint light;
	uint tank;
	uint hit2;
	uint medal;
	uint power;
	uint big_ship;
	uint big_tank;
	uint boss;

	fPoint returnFirstEnemyDir(int &enem);
	int hoamingReturnEnem(int enem);
	float hoamingReturnDirX(int enem);
	float hoamingReturnDirY(int enem);
	// Per al boss
	int retornCap();
	int moveCap(int enem, float x, float y);

	void CridaPrintSuperDown();

private:
	void SpawnEnemy(const EnemyInfo& info);

private:
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
};

#endif