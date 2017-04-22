#include "Application.h"
#include "Object_Medal.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
Object_Medal::Object_Medal(int x, int y) : Enemy(x, y) {
	Object_Medal_Animation.PushBack({ 119, 1, 8, 16 });
	Object_Medal_Animation.speed = 0.2f;
	Object_Medal_Animation.loop = false;
	animation = &Object_Medal_Animation;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 8, 16 }, COLLIDER_TYPE::COLLIDER_OBJECT_NO_COLLISION, (Module*)App->enemies);
	//original_y = y;
}

void Object_Medal::Move() {
	position.y += App->background->speedBackGround;
}

void Object_Medal::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER) {
		vida--;
	}
}
void Object_Medal::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->enemies->sprite_Medal_PowerUp_Bonus, position.x, position.y, &(animation->GetCurrentFrame()));
}