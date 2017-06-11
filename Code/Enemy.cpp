#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"

Enemy::Enemy(int x, int y) : position(x, y) {
}

Enemy::~Enemy(){
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const{
	return collider;
}

void Enemy::DrawUp(){}
void Enemy::DrawDown() {}
void Enemy::DrawSuperDown() {}

void Enemy::OnCollision(Collider* collider){

}