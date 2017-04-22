#include "Application.h"
#include "Object_PowerUp.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBullets.h"

Object_PowerUp::Object_PowerUp(int x, int y) : Enemy(x, y) {
	Object_PowerUp_Animation.PushBack({ 2, 2, 15, 13 });
	Object_PowerUp_Animation.speed = 0.2f;
	Object_PowerUp_Animation.loop = false;
	animation = &Object_PowerUp_Animation;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 15, 13 }, COLLIDER_TYPE::COLLIDER_OBJECT_NO_COLLISION, (Module*)App->enemies);
	//original_y = y;
}

void Object_PowerUp::Move() {
	position.y += 1;
}

void Object_PowerUp::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER) {
		App->bullet->powerUpLevelPlayer1++;
		vida--;
	}
	else if (collider->type == COLLIDER_PLAYER2) {
		App->bullet->powerUpLevelPlayer2++;
		vida--;
	}
}
void Object_PowerUp::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_Medal_PowerUp_Bonus, position.x, position.y, &(animation->GetCurrentFrame()));
}