#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_LightShooter.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies(){
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies(){}

bool ModuleEnemies::Start(){
	sprite_LightShooter = App->textures->Load("Sprites/Enemies/Stage_1/Light_Shooter.png");
	sprites2 = App->textures->Load("Sprites/Enemies/Stage_1/Tank.png");

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

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)	enemies[i]->Draw(/*sprites*/);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate(){
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i){
		if (enemies[i] != nullptr){
			if (enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y + App->render->camera.h)){
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
	//App->textures->Unload(sprite_LightShooter); S'HAN DE DESTRUIR LES NOVES TEXTURES !!!!!!

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
			//queue[i].type = ENEMY_TYPES::LIGHT_SHOOTER;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2){
	for (uint i = 0; i < MAX_ENEMIES; ++i){
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1){
			enemies[i]->OnCollision(c2);
			if (enemies[i]->vida <= 0) {
				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;
		}
	}
}