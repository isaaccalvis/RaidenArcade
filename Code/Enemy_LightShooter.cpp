#include "Application.h"
#include "Enemy_LightShooter.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

Enemy_LightShooter::Enemy_LightShooter(int x, int y) : Enemy(x, y){

	lightShooterAnim.PushBack({ 24,27,21,28 });
	lightShooterAnim.speed = 0.2f;
	lightShooterAnim.loop = false;
	animation = &lightShooterAnim;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
	vida = 1;
}

void Enemy_LightShooter::Draw(/*SDL_Texture* sprites*/) {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_LightShooter, position.x, position.y, &(animation->GetCurrentFrame()));
}
void Enemy_LightShooter::Move(){
	position.y += 1;
}

void Enemy_LightShooter::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		print("LightShooter receiv damage\n");
		vida--;
	}

	//vida -= dany;
}
