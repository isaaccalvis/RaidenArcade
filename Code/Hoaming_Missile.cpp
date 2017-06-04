#include "Application.h"
#include "Hoaming_Missile.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleBullets.h"

Hoaming_Missile::Hoaming_Missile(int x, int y) : Enemy(x, y) {
	vida = 1;
	fase = -1;
	animation = &Hoaming_Missile_Animation11;
	current_time = 0;
	dispara = false;
	enemicApuntant = -1;
	type = HOAMING_MISSILE;

	Hoaming_Missile_Animation.PushBack({ 160, 399, 16, 16 });
	Hoaming_Missile_Animation.PushBack({ 176, 399, 16, 16 });

	Hoaming_Missile_Animation1.PushBack({ 192, 399, 16, 16 });
	Hoaming_Missile_Animation1.PushBack({ 208, 399, 16, 16 });

	Hoaming_Missile_Animation2.PushBack({ 64, 383, 16, 16 });
	Hoaming_Missile_Animation2.PushBack({ 80, 383, 16, 16 });

	Hoaming_Missile_Animation3.PushBack({ 96, 383, 16, 16 });
	Hoaming_Missile_Animation3.PushBack({ 112, 383, 16, 16 });

	Hoaming_Missile_Animation4.PushBack({ 128, 383, 16, 16 });
	Hoaming_Missile_Animation4.PushBack({ 144, 383, 16, 16 });

	Hoaming_Missile_Animation5.PushBack({ 160, 383, 16, 16 });
	Hoaming_Missile_Animation5.PushBack({ 176, 383, 16, 16 });

	Hoaming_Missile_Animation6.PushBack({ 192, 383, 16, 16 });
	Hoaming_Missile_Animation6.PushBack({ 208, 383, 16, 16 });

	Hoaming_Missile_Animation7.PushBack({ 224, 383, 16, 16 });
	Hoaming_Missile_Animation7.PushBack({ 240, 383, 16, 16 });

	Hoaming_Missile_Animation8.PushBack({ 256, 383, 16, 16 });
	Hoaming_Missile_Animation8.PushBack({ 272, 383, 16, 16 });

	Hoaming_Missile_Animation9.PushBack({ 32, 383, 16, 16 });
	Hoaming_Missile_Animation9.PushBack({ 48, 383, 16, 16 });

	Hoaming_Missile_Animation10.PushBack({ 0, 399, 16, 16 });
	Hoaming_Missile_Animation10.PushBack({ 17, 399, 16, 16 });

	Hoaming_Missile_Animation11.PushBack({ 0, 384, 16, 16 });
	Hoaming_Missile_Animation11.PushBack({ 16, 384, 16, 16 });

	Hoaming_Missile_Animation12.PushBack({ 32, 383, 16, 16 });
	Hoaming_Missile_Animation12.PushBack({ 48, 383, 16, 16 });

	Hoaming_Missile_Animation13.PushBack({ 64, 399, 16, 16 });
	Hoaming_Missile_Animation13.PushBack({ 80, 399, 16, 16 });

	Hoaming_Missile_Animation14.PushBack({ 96, 399, 16, 16 });
	Hoaming_Missile_Animation14.PushBack({ 112, 399, 16, 16 });

	Hoaming_Missile_Animation15.PushBack({ 128, 399, 16, 16 });
	Hoaming_Missile_Animation15.PushBack({ 144, 399, 16, 16 });

	Hoaming_Missile_Animation16.PushBack({ 224, 399, 16, 16 });
	Hoaming_Missile_Animation16.PushBack({ 240, 399, 16, 16 });

	if(App->bullet->quiDisparaHoaming == 2) // Aixo es si el dispara el player 2
		collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_PLAYER2_SHOT, (Module*)App->enemies);
	else		// Aixo es si el dispara el player 1
		collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_PLAYER_SHOT, (Module*)App->enemies);

}

void Hoaming_Missile::Move() {
	// Moviment
	enemicApuntant = App->enemies->hoamingReturnEnem(enemicApuntant);
	dirX = App->enemies->hoamingReturnDirX(enemicApuntant);
	dirY = App->enemies->hoamingReturnDirY(enemicApuntant);
	if (enemicApuntant >= 0) {
		rectaY = position.y - dirY;
		rectaX = position.x - dirX;
		float angle = atan2(rectaX, rectaY);
		// Canvi d'Sprite i de direccio
		{
			if (angle > 0) {
				if (angle >= 2.625f) {
					animation = &Hoaming_Missile_Animation5;
					position.x -= 0;
					position.y += 4;
				}
				else if (angle >= 2.25f) {
					animation = &Hoaming_Missile_Animation6;
					position.x -= 2;
					position.y += 4;
				}
				else if (angle >= 1.875f) {
					animation = &Hoaming_Missile_Animation7;
					position.x -= 4;
					position.y += 2;
				}
				else if (angle >= 1.5f) {
					animation = &Hoaming_Missile_Animation8;
					position.x -= 4;
					position.y += 0;
				}
				else if (angle >= 1.25f) {
					animation = &Hoaming_Missile_Animation11;
					position.x -= 4;
					position.y -= 2;
				}
				else if (angle >= 0.75f) {
					animation = &Hoaming_Missile_Animation11;
					position.x -= 4;
					position.y -= 4;
				}
				else if (angle >= 0.375f) {
					position.x -= 2;
					position.y -= 4;
					animation = &Hoaming_Missile_Animation11;
				}
				else if (angle >= 0) {
					animation = &Hoaming_Missile_Animation10;
					position.y -= 4;
				}
			}
			else {
				if (angle < 0) {
					if (angle <= -2.625f) {
						animation = &Hoaming_Missile_Animation15;
						position.x -= 0;
						position.y += 4;
					}
					else if (angle <= -2.25f) {
						animation = &Hoaming_Missile_Animation3;
						position.x += 2;
						position.y += 4;
					}
					else if (angle <= -1.875f) {
						animation = &Hoaming_Missile_Animation13;
						position.x += 4;
						position.y += 2;
					}
					else if (angle <= -1.5f) {
						animation = &Hoaming_Missile_Animation12;
						position.x += 4;
						position.y += 0;
					}
					else if (angle <= -1.25f) {
						animation = &Hoaming_Missile_Animation12;
						position.x += 4;
						position.y -= 2;
					}
					else if (angle <= -0.75f) {
						animation = &Hoaming_Missile_Animation12;
						position.x += 4;
						position.y -= 4;
					}
					else if (angle <= -0.375f) {
						animation = &Hoaming_Missile_Animation12;
						position.x += 2;
						position.y -= 4;
					}
					else if (angle <= -0) {
						animation = &Hoaming_Missile_Animation10;
						position.y -= 4;
					}
				}
			}
		}
	}
	else {
		position.x += 0;
		position.y -= 5;
		animation = &Hoaming_Missile_Animation11;
	}
}

void Hoaming_Missile::OnCollision(Collider* collider) {
	vida--;
}

void Hoaming_Missile::DrawDown() {
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (animation != nullptr)
		App->render->fBlit(App->particles->particles_sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}