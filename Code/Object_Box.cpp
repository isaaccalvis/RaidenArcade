#include "Application.h"
#include "Object_Box.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleMusic.h"


Object_Box::Object_Box(int x, int y) : Enemy(x, y) {
	Object_Box_Animation.PushBack({ 0, 0, 25, 23 });
	Object_Box_Animation.speed = 0.2f;
	Object_Box_Animation.loop = false;
	animation = &Object_Box_Animation;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 25, 23 }, COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION, (Module*)App->enemies);
}

void Object_Box::Move() {
	position.y += App->background->speedBackGround;

}

void Object_Box::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT) {
		App->enemies->AddEnemy(MEDAL, (int)position.x + 11, (int)position.y) + 11;
		vida--;
		App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		//App->music->PlayFX(box);
	}
	else if (collider->type == COLLIDER_PLAYER2_SHOT) {
		App->enemies->AddEnemy(MEDAL, (int)position.x + 11, (int)position.y) + 11;
		vida--;
		App->particles->AddParticle(App->particles->HeavyExplosion, position.x, position.y, COLLIDER_NONE);
		//App->music->PlayFX(box);
	}	
}
void Object_Box::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_Box, position.x, position.y, &(animation->GetCurrentFrame()));
}