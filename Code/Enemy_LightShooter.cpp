#include "Application.h"
#include "Enemy_LightShooter.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"

Enemy_LightShooter::Enemy_LightShooter(int x, int y) : Enemy(x, y){

	lightShooterAnim.PushBack({ 24,27,21,28 });
	lightShooterAnim.speed = 0.2f;
	lightShooterAnim.loop = false;
	animation = &lightShooterAnim;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
}

void Enemy_LightShooter::Move(){
	/*
	if (going_up){
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}*/

//	position.y = original_y + (25.0f * sinf(wave));
	position.x -= 1;
}