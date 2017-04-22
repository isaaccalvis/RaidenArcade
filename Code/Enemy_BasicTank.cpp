#include "Application.h"
#include "Enemy_BasicTank.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

Enemy_BasicTank::Enemy_BasicTank(int x, int y) : Enemy(x, y) {
	Enemy_BasicTank_Animation.PushBack({ 11, 15, 22, 30 });
	Enemy_BasicTank_Animation.speed = 0.2f;
	Enemy_BasicTank_Animation.loop = false;
	animation = &Enemy_BasicTank_Animation;

	vida = 2;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//original_y = y;
}

void Enemy_BasicTank::Move() {
	//Moviment 1
	//el tanc esta quiet

	//Moviment 2 diagonal superior
	if(position.y<50){
	position.x += 1;
	position.y -= 1;
	}
	
	//Moviment 3
	position.x -= 1;
	position.y += 2;
	if (position.y > 50) {
	position.x += 1;
	position.y += 1;
	}

	//Moviment 4
	
	if(position.y<75)
	position.y -= 1;
	
	//Moviment 5
	if (position.y < 50) {
	position.x -= 1;
	position.y += 1;
	}
	//Moviment 6
	if(position.x>90)
	position.x += 1;

}

void Enemy_BasicTank::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT)
		vida--;
}
void Enemy_BasicTank::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_BasicTank, position.x, position.y, &(animation->GetCurrentFrame()));
}