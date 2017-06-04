#include "Application.h"
#include "Object_MissileUp.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBullets.h"
#include "ModuleMusic.h"
#include "SDL\include\SDL_timer.h"


Object_MissileUp::Object_MissileUp(int x, int y) : Enemy(x, y) {
	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 15, 13 }, COLLIDER_TYPE::COLLIDER_OBJECT_NO_COLLISION, (Module*)App->enemies);
	original_pos.y = y;
	original_pos.x = x;
	current_time = SDL_GetTicks() + 1500;
	MissileUpState = NuclearM;

	// vermell
	Object_PowerUp_Animation_Homing.PushBack({ 2, 19, 15, 13 });
	Object_PowerUp_Animation_Homing.PushBack({ 22, 19, 15, 13 });
	Object_PowerUp_Animation_Homing.PushBack({ 41, 19, 15, 13 });
	Object_PowerUp_Animation_Homing.speed = 0.2f;
	Object_PowerUp_Animation_Homing.loop = true;
	// blau
	Object_PowerUp_Animation_Nuclear.PushBack({ 59, 19, 15, 13 });
	Object_PowerUp_Animation_Nuclear.PushBack({ 78, 19, 15, 13 });
	Object_PowerUp_Animation_Nuclear.PushBack({ 96, 19, 15, 13 });
	Object_PowerUp_Animation_Nuclear.speed = 0.2f;
	Object_PowerUp_Animation_Nuclear.loop = true;

	animation = &Object_PowerUp_Animation_Nuclear;

	//
	path.PushBack({ 0.6f,0.6f }, 10, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 15, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 20, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 25, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	//
	path.PushBack({ 0.6f,0.6f }, 35, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 45, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 55, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 65, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	//
	path.PushBack({ 0.6f,0.6f }, 75, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 85, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 95, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 105, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	//
	path.PushBack({ 0.6f,0.6f }, 115, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 125, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 135, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 145, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	//
	path.PushBack({ 0.6f,0.6f }, 155, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 165, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 175, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 185, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	//
	path.PushBack({ 0.6f,0.6f }, 195, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.6f }, 205, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,0.0f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ -0.6f,-0.6f }, 215, &Object_PowerUp_Animation);
	path.PushBack({ 0.0f,-0.6f }, 5, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,-0.6f }, 225, &Object_PowerUp_Animation);
	path.PushBack({ 0.6f,0.0f }, 5, &Object_PowerUp_Animation);

	path.PushBack({ -0.6f,-0.6f }, 300, &Object_PowerUp_Animation);


}

void Object_MissileUp::Move() {
	if (current_time < SDL_GetTicks()) {
		current_time = SDL_GetTicks() + 1500;
		if (MissileUpState == Nuclear) {
			MissileUpState = HomingM;
			animation = &Object_PowerUp_Animation_Homing;
		}
		else {
			MissileUpState = NuclearM;
			animation = &Object_PowerUp_Animation_Nuclear;
		}
	}
	position = original_pos + path.fGetCurrentPosition();
}

void Object_MissileUp::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER) {
		if (MissileUpState == NuclearM)
			App->bullet->missileUpTypePlayer1 = Nuclear;
		else
			App->bullet->missileUpTypePlayer1 = Hoaming;
		App->bullet->missileUpLevelPlayer1++;
		vida--;
	}
	else if (collider->type == COLLIDER_PLAYER2) {
		if (MissileUpState == NuclearM)
			App->bullet->missileUpTypePlayer2 = Nuclear;
		else
			App->bullet->missileUpTypePlayer2 = Hoaming;
		App->bullet->missileUpLevelPlayer2++;
		vida--;
	}
}
void Object_MissileUp::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_Medal_PowerUp_Bonus, position.x, position.y, &(animation->GetCurrentFrame()));
}