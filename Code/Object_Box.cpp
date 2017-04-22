#include "Application.h"
#include "Object_Box.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleEnemies.h"

Object_Box::Object_Box(int x, int y) : Enemy(x, y) {
	Object_Box_Animation.PushBack({ 11, 15, 24, 24 });
	Object_Box_Animation.speed = 0.2f;
	Object_Box_Animation.loop = false;
	animation = &Object_Box_Animation;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
	//original_y = y;
}

void Object_Box::Move() {
	position.y += App->background->speedBackGround;
}

void Object_Box::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		App->enemies->AddEnemy(MEDAL, (int)position.x + 11, (int)position.y) + 11;
		vida--;
	}
}
void Object_Box::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_Box, position.x, position.y, &(animation->GetCurrentFrame()));
}