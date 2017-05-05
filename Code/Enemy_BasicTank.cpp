#include "Application.h"
#include "Enemy_BasicTank.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"

Enemy_BasicTank::Enemy_BasicTank(int x, int y) : Enemy(x, y) {
	Enemy_BasicTank_Animation.PushBack({ 13, 25, 22, 25 });
	Enemy_BasicTank_Animation.speed = 0.2f;
	Enemy_BasicTank_Animation.loop = false;
	animation = &Enemy_BasicTank_Animation;

	vida = 2;
	collider = App->collision->AddCollider({ 0, 0, 22, 25 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
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
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		vida--;
		if (vida > 0)
			App->player->puntuacioP1 += 20;
		else
			App->player->puntuacioP1 += 130;

		if (vida <= 0)
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		vida--;
		if (vida > 0)
			App->player2->puntuacioP2 += 20;
		else
			App->player2->puntuacioP2 += 130;

		if (vida <= 0)
			App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		else
			App->particles->AddParticle(App->particles->restOfBulletCollision, position.x + 12, position.y + 12, COLLIDER_NONE);
	}

}
void Enemy_BasicTank::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_BasicTank, position.x /*collider->rect.x*/, position.y, &(animation->GetCurrentFrame()));
}