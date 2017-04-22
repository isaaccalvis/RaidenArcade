#include "Application.h"
#include "Enemy_LightShooter.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

Enemy_LightShooter::Enemy_LightShooter(int x, int y) : Enemy(x, y){
	LightShooterAnim.PushBack({ 11, 15, 22, 30 });
	LightShooterAnim.speed = 0.2f;
	LightShooterAnim.loop = false;
	animation = &LightShooterAnim;

	vida = 1;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//original_y = y;
}

void Enemy_LightShooter::Move() {
	if (fase == 0 && position.y < 150)
		if (position.y > 110 && position.y < 130)
			position.y += 2;
		else if (position.y > 130)
			position.y += 1;
		else
			position.y += 3;
	else
		fase = 1;
	if (fase == 1)
		if (position.y > 150 && position.y < 130)
			position.y -= 1;
		else if (position.y > 130)
			position.y -= 2;
		else
			position.y -= 3;
}

void Enemy_LightShooter::OnCollision(Collider* collider) {
	if (collider->type == COLLIDER_PLAYER_SHOT)
		vida--;
}

void Enemy_LightShooter::Draw() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(App->enemies->sprite_LightShooter, position.x, position.y, &(animation->GetCurrentFrame()));
}

//Animación Giro Sin Hélices
/*
11, 15, 22, 30
35, 44, 32, 28
39, 16, 32, 30
103, 15, 27, 26
132, 15, 27, 25
161, 15, 27, 26
190, 15, 22, 30
214, 15, 27, 25
*/

/*

***************************
******POSICIONES TANK******
***************************

Posiciones Tank sin gun:

13, 25, 23, 25
40, 26, 30, 16
72, 22, 30, 29
104, 22, 30, 28
137, 22, 29, 29
167, 24, 31, 25
200, 24, 30, 26
233, 23, 29, 28
269, 24, 23, 25
296, 26, 30, 16
328, 21, 30, 29
360, 21, 29, 28
392, 21, 29, 29
422, 23, 31, 25
455, 23, 30, 26
488, 22, 29, 28
524, 23, 23, 25
551, 24, 30, 16
583, 21, 30, 29
615, 21, 30, 28
648, 21, 29, 29
678, 23, 31, 25
711, 23, 30, 26
744, 22, 29, 28

Posiciones de la gun:

13, 69, 16, 24
36, 74, 27, 14
71, 64, 15, 25
96, 71, 27, 13
126, 71, 21, 20
157, 68, 21, 20
185, 67, 20, 21
216, 68, 21, 20
248, 65, 14, 23
269, 69, 24, 16
299, 69, 25, 17
333, 64, 16, 24
361, 65, 15, 24
389, 68, 25, 18
424, 67, 26, 18
456, 66, 16, 23
*/