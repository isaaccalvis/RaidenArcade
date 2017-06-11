#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_LightShooter.h"
#include "Enemy_BasicTank.h"
#include "Enemy_BonusPlane.h"
#include "Enemy_Turret.h"
#include "EnemyBomba.h"
#include "Object_Box.h"
#include "Object_Medal.h"
#include "Object_PowerUp.h"
#include "Object_MissileUp.h"
#include "Asteroid.h"
#include "DiamondPlane.h"
#include "HeavyOrangeAirship.h"
#include "HeavyTurret.h"
#include "LightShooterLateral.h"
#include "vTank.h"
#include "Hoaming_Missile.h"
#include "BossHead.h"
#include "BaseBoss.h"
#include "ModuleMusic.h"

#define SPAWN_MARGIN 100

ModuleEnemies::ModuleEnemies(){
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies(){}

bool ModuleEnemies::Start(){
	// Enemies BackGround 1
	sprite_LightShooter = App->textures->Load("Sprites/Enemies/Stage_1/Light_Shooter.png");
	sprite_BasicTank = App->textures->Load("Sprites/Enemies/Stage_1/Tank.png");
	sprite_Turret = App->textures->Load("Sprites/Enemies/Stage_1/Turret.png");
	sprite_BonusPlane = App->textures->Load("Sprites/Enemies/Stage_1/Bonus_Airship.png");
	sprite_enemyBomb = App->textures->Load("Sprites/Enemies/Stage_1/Mine.png");
	sprite_Box = App->textures->Load("Sprites/Extras/Box.png");
	sprite_Medal_PowerUp_Bonus = App->textures->Load("Sprites/Extras/Powerups_and_bonusues.png");

	// Enemies BackGround 6
	sprite_Asteroid = App->textures->Load("Sprites/Enemies/Stage_6/Asteroid.png");
	sprite_Diamond_Plane = App->textures->Load("Sprites/Enemies/Stage_6/Diamond_Plane.png");
	sprite_Heavy_Orange_Airship = App->textures->Load("Sprites/Enemies/Stage_6/Heavy_Orange_Ship.png");
	sprite_Light_Shooter_Lateral = App->textures->Load("Sprites/Enemies/Stage_6/Light_Shooter_Lateral.png");
	sprite_Heavy_Turret = App->textures->Load("Sprites/Enemies/Stage_6/Heavy_Turret.png");
	sprite_vTank = App->textures->Load("Sprites/Enemies/Stage_6/vTank.png");
	sprite_boss6 = App->textures->Load("Sprites/Enemies/Stage_6/Boss_6.png");

	// AUDIO FX
	light = App->music->LoadFX("Audio/Fx/Little_ship.wav");
	tank = App->music->LoadFX("Audio/Fx/Little_tank.wav");
	hit = App->music->LoadFX("Audio/Fx/Hit.wav");
	box = App->music->LoadFX("Audio/Fx/Box.wav");
	medal = App->music->LoadFX("Audio/Fx/Pick_points.wav");
	power = App->music->LoadFX("Audio/Fx/Power_up.wav");
	big_ship = App->music->LoadFX("Audio/Fx/Big_ship.wav");
	big_tank = App->music->LoadFX("Audio/Fx/Big_tank.wav");
	boss = App->music->LoadFX("Audio/Fx/Boss_death.wav");
	return true;
}

update_status ModuleEnemies::PreUpdate(){
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i){
		if (queue[i].type != ENEMY_TYPES::NO_TYPE){
			if (queue[i].y * SCREEN_SIZE < App->render->camera.y + (App->render->camera.h * SCREEN_SIZE) + SPAWN_MARGIN){
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update() {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->DrawDown();
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->DrawUp();
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate(){
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			if ((enemies[i]->position.y * SCREEN_SIZE) > (ORIGINAL_CAMERA_WEIGHT + App->render->camera.y + App->render->camera.h + SPAWN_MARGIN)) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
			else if (enemies[i]->position.y * SCREEN_SIZE < 0 - SPAWN_MARGIN/*(App->render->camera.y - SPAWN_MARGIN)*/) {
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemies::CleanUp(){
	App->textures->Unload(sprite_LightShooter);
	App->textures->Unload(sprite_BonusPlane);
	App->textures->Unload(sprite_Turret);
	App->textures->Unload(sprite_BasicTank);
	App->textures->Unload(sprite_Box);
	App->textures->Unload(sprite_Medal_PowerUp_Bonus);
	App->textures->Unload(sprite_Asteroid);
	App->textures->Unload(sprite_Diamond_Plane);
	App->textures->Unload(sprite_Heavy_Orange_Airship);
	App->textures->Unload(sprite_Heavy_Turret);
	App->textures->Unload(sprite_Light_Shooter_Lateral);
	App->textures->Unload(sprite_vTank);
	App->textures->Unload(sprite_boss6);
	App->textures->Unload(sprite_enemyBomb);

	App->music->UnloadFX(light);
	App->music->UnloadFX(tank);
	App->music->UnloadFX(hit);
	App->music->UnloadFX(box);
	App->music->UnloadFX(medal);
	App->music->UnloadFX(power);
	App->music->UnloadFX(big_ship);
	App->music->UnloadFX(big_tank);
	App->music->UnloadFX(boss);

	for (uint i = 0; i < MAX_ENEMIES; ++i){
		if (enemies[i] != nullptr){
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y){
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i){
		if (queue[i].type == ENEMY_TYPES::NO_TYPE){
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}
	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info){
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);
	if (i != MAX_ENEMIES){
		switch (info.type){
		case ENEMY_TYPES::LIGHT_SHOOTER:
			enemies[i] = new Enemy_LightShooter(info.x, info.y);
			enemies[i]->type = LIGHT_SHOOTER;
			break;
		case ENEMY_TYPES::BASIC_TANK:
			enemies[i] = new Enemy_BasicTank(info.x, info.y);
			enemies[i]->type = BASIC_TANK;
			break;
		case ENEMY_TYPES::BONUS_PLANE:
			enemies[i] = new Enemy_BonusPlane(info.x, info.y);
			enemies[i]->type = BONUS_PLANE;
			break;
		case ENEMY_TYPES::TURRET:
			enemies[i] = new Enemy_Turret(info.x, info.y);
			enemies[i]->type = TURRET;
			break;
		case ENEMY_TYPES::BOMB:
			enemies[i] = new Enemy_Bomb(info.x, info.y);
			enemies[i]->type = BOMB;
			break;
		case ENEMY_TYPES::BOX:
			enemies[i] = new Object_Box (info.x, info.y);
			enemies[i]->type = BOX;
			break;
		case ENEMY_TYPES::MEDAL:
			enemies[i] = new Object_Medal(info.x, info.y);
			enemies[i]->type = MEDAL;
			break;
		case ENEMY_TYPES::POWER_UP:
			enemies[i] = new Object_PowerUp(info.x, info.y);
			enemies[i]->type = POWER_UP;
			break;
		case ENEMY_TYPES::MISSILE_UP:
			enemies[i] = new Object_MissileUp(info.x, info.y);
			enemies[i]->type = MISSILE_UP;
			break;
		case ENEMY_TYPES::ASTEROID:
			enemies[i] = new Asteroid(info.x, info.y);
			enemies[i]->type = ASTEROID;
			break;
		case ENEMY_TYPES::DIAMOND_PLANE:
			enemies[i] = new DiamondPlane(info.x, info.y);
			enemies[i]->type = DIAMOND_PLANE;
			break;
		case ENEMY_TYPES::HEAVY_ORANGE_AIRSHIP:
			enemies[i] = new HeavyOrangeAirship(info.x, info.y);
			enemies[i]->type = HEAVY_ORANGE_AIRSHIP;
			break;
		case ENEMY_TYPES::HEAVY_TURRET:
			enemies[i] = new HeavyTurret(info.x, info.y);
			enemies[i]->type = HEAVY_TURRET;
			break;
		case ENEMY_TYPES::LIGHT_SHOOTER_LATERAL:
			enemies[i] = new LightShooterLateral(info.x, info.y);
			enemies[i]->type = LIGHT_SHOOTER_LATERAL;
			break;
		case ENEMY_TYPES::VTANK:
			enemies[i] = new vTank(info.x, info.y);
			enemies[i]->type = VTANK;
			break;
		case ENEMY_TYPES::HOAMING_MISSILE:
			enemies[i] = new Hoaming_Missile(info.x, info.y);
			enemies[i]->type = HOAMING_MISSILE;
			break;
		case ENEMY_TYPES::BOSS6_HEAD:
			enemies[i] = new bossHead(info.x, info.y);
			enemies[i]->type = BOSS6_HEAD;
			break;
		case ENEMY_TYPES::BOSS6_BASE:
			enemies[i] = new Base_Boss(info.x, info.y);
			enemies[i]->type = BOSS6_BASE;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {
			enemies[i]->OnCollision(c2);
			if (enemies[i]->type == BASIC_TANK || enemies[i]->type == LIGHT_SHOOTER || enemies[i]->type == LIGHT_SHOOTER_LATERAL || enemies[i]->type == HOAMING_MISSILE) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else {
					App->music->PlayFX(light);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == BONUS_PLANE || enemies[i]->type == ASTEROID || enemies[i]->type == DIAMOND_PLANE ||enemies[i]->type == BOMB) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else {
					App->music->PlayFX(big_ship);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == TURRET || enemies[i]->type == HEAVY_TURRET) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else  {
					App->music->PlayFX(tank);
				}

			}
			else if (enemies[i]->type == BOX) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else {
					App->music->PlayFX(box);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == MEDAL) {
				if (enemies[i]->vida <= 0) {
					App->music->PlayFX(medal);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == POWER_UP || enemies[i]->type == MISSILE_UP) {
				if (enemies[i]->vida <= 0) {
					App->music->PlayFX(power);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == VTANK || enemies[i]->type == BOSS6_HEAD) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else {
					App->music->PlayFX(big_tank);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			else if (enemies[i]->type == HEAVY_ORANGE_AIRSHIP) {
				if (enemies[i]->vida > 0)
					App->music->PlayFX(hit);
				else {
					App->music->PlayFX(boss);
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
		}
	}
}
fPoint ModuleEnemies::returnFirstEnemyDir(int &enem) {
	if (enem == -1) {
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemies[i] != nullptr) {
				i = MAX_ENEMIES;
				enem = i;
			}
		}
	}
	return enemies[enem]->position;
}

int ModuleEnemies::hoamingReturnEnem(int enem) {
	if (enem < 0) {
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemies[i] != nullptr && enemies[i]->type != HOAMING_MISSILE && enemies[i]->type != MISSILE_UP && enemies[i]->type != POWER_UP && enemies[i]->type != MEDAL && enemies[i]->type != BOSS6_BASE && enemies[i]->type != HEAVY_TURRET_DESTROY && enemies[i]->position.y < SCREEN_HEIGHT) {
				return i;
			}
		}
	} else {
		if (enemies[enem] != nullptr)
			return enem;
		else
			return -1;
	}
	return -1;
}
float ModuleEnemies::hoamingReturnDirX(int enem) {
	if (enem < 0)
		return 0;
	else
		if (enemies[enem] != nullptr)
			return enemies[enem]->position.x;
}
float ModuleEnemies::hoamingReturnDirY(int enem) {
	if (enem < 0)
		return 0;
	else
		if (enemies[enem] != nullptr)
			return enemies[enem]->position.y;
}

int ModuleEnemies::retornCap() {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i] == nullptr) {
			enemies[i] = new bossHead(-1 , -1);
			enemies[i]->type = BOSS6_HEAD;
			return i;
		}
	}
}


int ModuleEnemies::moveCap(int enem, float x, float y) {
	if (enemies[enem] != nullptr) {
		enemies[enem]->position.x = x;
		enemies[enem]->position.y = y;
		return enem;
	}
	else
		return -1;
}

void ModuleEnemies::CridaPrintSuperDown() {
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->DrawSuperDown();
}