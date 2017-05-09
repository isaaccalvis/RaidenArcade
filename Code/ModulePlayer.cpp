#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleBullets.h"
#include "ModuleEnemies.h"
#include "ModuleMenuScreen.h"
#include "ModuleFonts.h"
#include "ModuleBackground.h"

#include "SDL\include\SDL_timer.h"

ModulePlayer::ModulePlayer(){
	current_animation = NULL;
	PROTA.w = 26;
	PROTA.h = 30;

	idle.PushBack({ 84, 19, 24, 34 });
	idle.PushBack({ 84, 61, 24, 34 });
	idle.speed = 0.4;

	rightMov.PushBack({ 117,19,21,34 });
	rightMov.PushBack({ 117,61,21,34 });
	rightMov.PushBack({ 151,19,16,34 });
	rightMov.PushBack({ 151,61,16,34 });
	rightMov.loop = false;
	rightMov.speed = 0.3f;

	rightMov2.PushBack({ 151,19,16,34 });
	rightMov2.PushBack({ 151,61,16,34 });
	rightMov2.loop = true;
	rightMov2.speed = 0.4f;

	leftMov.PushBack({ 52,19,24,34 });
	leftMov.PushBack({ 52,61,24,34 });
	leftMov.PushBack({ 18,19,24,34 });
	leftMov.PushBack({ 18,61,24,34 });
	leftMov.loop = false;
	leftMov.speed = 0.3f;

	leftMov2.PushBack({ 18,19,24,34 });
	leftMov2.PushBack({ 18,61,24,34 });
	leftMov2.loop = true;
	leftMov2.speed = 0.4f;

	pDamaged.PushBack({ 84, 19, 24, 34 });
	pDamaged.PushBack({ 500, 550, 24, 34 });

	pDead.PushBack({ 240,667,28,29 });
	pDead.PushBack({ 272,667,28,29 });
	pDead.PushBack({ 305,667,30,31 });
	pDead.PushBack({ 399,665,32,30 });
	pDead.speed = 0.2f;
	pDead.loop = false;

	Despegar1.PushBack({ 422,89,32,70 });
	Despegar1.PushBack({ 457,89,32,70 });
	Despegar1.PushBack({ 492,89,32,70 });
	Despegar1.PushBack({ 531,89,32,70 });
	Despegar1.PushBack({ 567,89,32,70 });
	Despegar1.speed = 0.6f;

	Despegar2.PushBack({ 499,163,32,70 });
	Despegar2.PushBack({ 533,163,32,70 });
	Despegar2.PushBack({ 499,163,32,70 });
	Despegar2.PushBack({ 533,163,32,70 });
	Despegar2.PushBack({ 499,163,32,70 });
	Despegar2.PushBack({ 533,163,32,70 });
	Despegar2.speed = 0.6f;

	Despegar3.PushBack({ 504,21,32,68 });
	Despegar3.PushBack({ 540,21,32,68 });
	Despegar3.PushBack({ 84, 19, 24, 34 });
	Despegar3.speed = 0.6f;

}

ModulePlayer::~ModulePlayer(){}

bool ModulePlayer::Start(){
	potMoure = true;
	puntuacioP1 = 0;
	videsP1 = 3;
	bool ret = true;
	App->player->Enable();
	App->bullet->Enable();
	App->collision->Enable();

	if (App->player2->jugador2Activat == false) {
		PROTA.x = SCREEN_WIDTH / 2 - PROTA.w / 2;
		PROTA.y = SCREEN_HEIGHT / 2;
	} else {
		PROTA.x = 140;
		PROTA.y = SCREEN_HEIGHT / 2;
	}
	graphics = App->textures->Load("Sprites/Player/Players.png");
	colPlayer1 = App->collision->AddCollider(PROTA, COLLIDER_PLAYER, this);
	font_score = App->fonts->Load("fonts/raiden_font.png", "! @,-./0123456789$;>&?abcdefghijklmnopqrstuvwxyz", 1);
	App->bullet->powerUpLevelPlayer1 = 0;

	return ret;
}

update_status ModulePlayer::Update(){
	int speed = 2;
	if (potMoure == true) {
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			if (PROTA.x < (SCREEN_WIDTH - PROTA.w))
				PROTA.x += speed;
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &rightMov)
				current_animation = &rightMov2;
			if (current_animation != &rightMov && current_animation != &rightMov2) {
				rightMov.Reset();
				current_animation = &rightMov;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			if (PROTA.x > (0))
				PROTA.x -= speed;
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &leftMov)
				current_animation = &leftMov2;
			if (current_animation != &leftMov && current_animation != &leftMov2) {
				leftMov.Reset();
				current_animation = &leftMov;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && PROTA.y > 0) {
			PROTA.y -= speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && PROTA.y < SCREEN_HEIGHT - PROTA.w) {
			PROTA.y += speed;
		}
		if (GodMode == true) {
			if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(LIGHT_SHOOTER, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(BASIC_TANK, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(BONUS_PLANE, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(TURRET, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(BOX, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(MEDAL, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN)
				App->enemies->AddEnemy(POWER_UP, PROTA.x, 0);
		}
		if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
			if (GodMode == false)
				GodMode = true;
			else
				GodMode = false;
		/// CORRECTOR DE LIMITS
		if (PROTA.x < 0)
			PROTA.x = 0;
		if (PROTA.x > (SCREEN_WIDTH - PROTA.w))
			PROTA.x = SCREEN_WIDTH - PROTA.w;
		if (PROTA.y < 0)
			PROTA.y = 0;
		if (PROTA.y > SCREEN_HEIGHT)
			PROTA.y = SCREEN_HEIGHT;

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			current_animation = &idle;
		else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
			&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
			current_animation = &idle;
	}
	print("%i %i\n", leftMov.IntCurrentFrame(), rightMov.IntCurrentFrame());

	App->fonts->BlitText(60, 10, font_score, "1up");
	if (videsP1 == 4) {
		App->fonts->BlitText(10, 20, font_score, "&");
		App->fonts->BlitText(19, 20, font_score, "&");
		App->fonts->BlitText(28, 20, font_score, "&");
	}
	else if (videsP1 == 3) {
		App->fonts->BlitText(10, 20, font_score, "&");
		App->fonts->BlitText(19, 20, font_score, "&");
	}
	else if (videsP1 == 2)
		App->fonts->BlitText(10, 20, font_score, "&");

	colPlayer1->SetPos(PROTA.x, PROTA.y);

	/*App->fonts->BlitText(180, 10, font_score, "hi-score");
	char str[10];
	sprintf_s(str, "%i", puntuacioP1);
	App->fonts->BlitText(200,s 25, font_score, str);
	sprintf_s(score_text, 10, "%7d", puntuacioP1);*/

		/// Draw everything --------------------------------------
	// Restaurador de quan et fots una hostia
	if (destroyed == true) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 2000)) {
			if (videsP1 > 0) {
				current_animation = &pDamaged;
				PROTA.x = SCREEN_WIDTH / 2 - PROTA.w / 2;
				PROTA.y = SCREEN_HEIGHT / 2 + 30;
			}
		}
		else
			current_animation = &pDead;
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {	
			destroyed = false;
			potMoure = true;
			App->bullet->powerUpLevelPlayer1 = 0;
			// CUANDO LA PALMA
			if (videsP1 <= 0) {
				if (App->player2->IsEnabled() == true && App->player2->videsP2 > 0) {
					colPlayer1->SetPos(9999, 0);
					App->player->CleanUp();
					App->player->potMoure = false;
				}
				else {
					App->background->CleanUp();
					App->player->CleanUp();
					App->enemies->CleanUp();
					App->player2->CleanUp();
					App->menuScreen->Enable();
					App->menuScreen->CridaMenu();
				}
			}
		}
	}

	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, PROTA.x, PROTA.y, &r);

	App->background->CridaScoreGeneral();

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp(){
	bool ret = true;
	App->textures->Unload(graphics);
	App->player->Disable();
	if (App->player2->IsEnabled() == false && App->player2->videsP2 <= 0) {
		App->collision->Disable();
		App->bullet->Disable();
	}
	return ret;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT) && destroyed == false && GodMode == false) {
		videsP1--;

		current_time = SDL_GetTicks() + 3000;
		current_animation = &pDead;
		current_animation->Reset();
		potMoure = false;
		destroyed = true;
	}
}