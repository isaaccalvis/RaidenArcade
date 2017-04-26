#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

Enemy::Enemy(int x, int y) : position(x, y) {
	//hit = App->music->LoadFX("Audio/Fx/hit.wav");
	//Bonus = App->music->LoadFX("Audio/Fx/Big ship.wav");
	//box = App->music->LoadFX("Audio/Fx/Box and tank.wav");
	//light = App->music->LoadFX("Audio/Fx/Little ship.wav");
	//tank = App->music->LoadFX("Audio/Fx/Big ship.wav");
	//hit2 = App->music->LoadFX("Audio/Fx/Hit.wav");
	//medal = App->music->LoadFX("Audio/Fx/Pick points.wav");
	//power = App->music->LoadFX("Audio/Fx/Power-up.wav");
}

Enemy::~Enemy(){
	if (collider != nullptr)
		collider->to_delete = true;
	//App->music->UnloadFX(hit);
	//App->music->UnloadFX(Bonus);
	//App->music->UnloadFX(box);
	//App->music->UnloadFX(light);
	//App->music->UnloadFX(tank);
	//App->music->UnloadFX(hit2);
	//App->music->UnloadFX(medal);
	//App->music->UnloadFX(power);
}

const Collider* Enemy::GetCollider() const{
	return collider;
}

void Enemy::DrawUp(){}
void Enemy::DrawDown() {}

void Enemy::OnCollision(Collider* collider){

}