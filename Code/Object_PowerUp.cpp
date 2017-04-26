#include "Application.h"
#include "Object_PowerUp.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBullets.h"
#include "ModuleMusic.h"


Object_PowerUp::Object_PowerUp(int x, int y) : Enemy(x, y) {
	

	
	Object_PowerUp_Animation.PushBack({ 2, 2, 15, 13 });
	Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });
	Object_PowerUp_Animation.PushBack({ 41, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 2, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 41, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 2, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 41, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 22, 2, 15, 13 });


	// blau
	//		//158
	//Object_PowerUp_Animation.PushBack({ 59, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 96, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 59, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 96, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 59, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 96, 2, 15, 13 });
	//Object_PowerUp_Animation.PushBack({ 78, 2, 15, 13 });
	

		Object_PowerUp_Animation.speed = 0.2f;
		Object_PowerUp_Animation.loop = true;
		animation = &Object_PowerUp_Animation;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 15, 13 }, COLLIDER_TYPE::COLLIDER_OBJECT_NO_COLLISION, (Module*)App->enemies);
	original_pos.y = y;
	original_pos.x = x;

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

void Object_PowerUp::Move() {
	position = original_pos + path.fGetCurrentPosition();
}

void Object_PowerUp::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER) {
		App->bullet->powerUpLevelPlayer1++;
		vida--;
		//App->music->PlayFX(power);
	}
	else if (collider->type == COLLIDER_PLAYER2) {
		App->bullet->powerUpLevelPlayer2++;
		vida--;
		//App->music->PlayFX(power);
	}
}
void Object_PowerUp::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_Medal_PowerUp_Bonus, position.x, position.y, &(animation->GetCurrentFrame()));
}