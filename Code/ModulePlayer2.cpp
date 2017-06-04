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

ModulePlayer2::ModulePlayer2() {
	current_animation = NULL;

	PROTA2.w = 26;
	PROTA2.h = 30;

	idle.PushBack({ 308, 19, 24, 34 });
	idle.PushBack({ 308, 61, 24, 34 });
	idle.speed = 0.4f;

	rightMov.PushBack({ 341,19,21,34 });
	rightMov.PushBack({ 341,61,21,34 });
	rightMov.PushBack({ 375,19,16,34 });
	rightMov.PushBack({ 375,61,16,34 });
	rightMov.loop = false;
	rightMov.speed = 0.4f;

	rightMov2.PushBack({ 375,19,16,34 });
	rightMov2.PushBack({ 375,61,16,34 });
	rightMov.loop = true;
	rightMov.speed = 0.4f;

	leftMov.PushBack({ 278,19,21,34 });
	leftMov.PushBack({ 278,61,21,34 });
	leftMov.PushBack({ 244,19,21,34 });
	leftMov.PushBack({ 244,61,21,34 });
	leftMov.loop = false;
	leftMov.speed = 0.4f;

	leftMov2.PushBack({ 244,19,21,34 });
	leftMov2.PushBack({ 244,61,21,34 });
	leftMov.loop = true;
	leftMov.speed = 0.4f;

	pDamaged.PushBack({ 308, 19, 24, 34 });
	pDamaged.PushBack({ 500, 550, 24, 34 });

	pDead.PushBack({ 240,667,28,29 });
	pDead.PushBack({ 272,667,28,29 });
	pDead.PushBack({ 305,667,30,31 });
	pDead.PushBack({ 399,665,32,30 });
	pDead.speed = 0.1f;
	pDead.loop = false;

	Despegar1.PushBack({ 422,384,32,70 });
	Despegar1.PushBack({ 457,384,32,70 });
	Despegar1.PushBack({ 492,384,30,70 });
	Despegar1.PushBack({ 531,384,30,70 });
	Despegar1.PushBack({ 567,384,30,70 });
	Despegar1.speed = 0.6f;

	Despegar2.PushBack({ 499,458,32,70 });
	Despegar2.PushBack({ 533,458,32,70 });
	Despegar2.PushBack({ 499,458,32,70 });
	Despegar2.PushBack({ 533,458,32,70 });
	Despegar2.PushBack({ 499,458,32,70 });
	Despegar2.PushBack({ 533,458,32,70 });
	Despegar2.speed = 0.6f;

	Despegar3.PushBack({ 504,316,32,60 });
	Despegar3.PushBack({ 540,316,32,60 });
	Despegar3.PushBack({ 308, 19, 24, 34 });
	Despegar3.speed = 0.6f;
}

ModulePlayer2::~ModulePlayer2() {}

bool ModulePlayer2::Start() {
	PROTA2.x = 190;
	PROTA2.y = SCREEN_HEIGHT / 2;
	puntuacioP2 = 0;
	potMoure2 = true;
	videsP2 = 3;
	bool ret = true;
	font_score2 = App->fonts->Load("fonts/raidenp2_font.png", "! @,-./0123456789$;>&?abcdefghijklmnopqrstuvwxyz", 1);
	font_score = App->fonts->Load("fonts/raiden_font.png", "! @,-./0123456789$;>&?abcdefghijklmnopqrstuvwxyz", 1);

	font_score = App->fonts->Load("fonts/raidenp2_font.png", "! @,-./0123456789$;>&?abcdefghijklmnopqrstuvwxyz", 1);
	LOG("Loading player textures");
	graphics = App->textures->Load("Sprites/Player/Players.png");
	colPlayer2 = App->collision->AddCollider(PROTA2, COLLIDER_PLAYER2, this);
	App->bullet->powerUpLevelPlayer2 = 0;
	App->menuScreen->highscore = -1;
	distanciaPlayers = 0;
	return ret;
}

update_status ModulePlayer2::Update() {
	distanciaPlayers = App->player->PROTA.x - PROTA2.x;

	int speed = 2;
	if (potMoure2 == true) {
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->dpadRight2 == KEY_STATE::KEY_REPEAT || App->input->joy_right2 == KEY_STATE::KEY_REPEAT) {
			if ((PROTA2.x < (SCREEN_WIDTH - PROTA2.w)) && distanciaPlayers > -198)
				PROTA2.x += speed;
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &rightMov)
				current_animation = &rightMov2;
			if (current_animation != &rightMov && current_animation != &rightMov2) {
				rightMov.Reset();
				current_animation = &rightMov;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft2 == KEY_STATE::KEY_REPEAT || App->input->joy_left2 == KEY_STATE::KEY_REPEAT) {
			if (PROTA2.x >(0) && distanciaPlayers < 198)
				PROTA2.x -= speed;
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &leftMov)
				current_animation = &leftMov2;
			if (current_animation != &leftMov && current_animation != &leftMov2) {
				leftMov.Reset();
				current_animation = &leftMov;
			}
		}
		if ((App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->dpadUp2 == KEY_STATE::KEY_REPEAT || App->input->joy_up2 == KEY_STATE::KEY_REPEAT) && PROTA2.y > 0) {
			PROTA2.y -= speed;
		}
		if ((App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT || App->input->dpadDown2 == KEY_STATE::KEY_REPEAT || App->input->joy_down2 == KEY_STATE::KEY_REPEAT) && PROTA2.y < SCREEN_HEIGHT - PROTA2.h) {
			PROTA2.y += speed;
		}

		// CORRECTOR DE LIMITS
		if (PROTA2.x < 0)
			PROTA2.x = 0;
		if (PROTA2.x > (SCREEN_WIDTH - PROTA2.w))
			PROTA2.x = SCREEN_WIDTH - PROTA2.w;
		if (PROTA2.y < 0)
			PROTA2.y = 0;
		if (PROTA2.y > SCREEN_HEIGHT)
			PROTA2.y = SCREEN_HEIGHT;

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE && App->input->dpadLeft2 == KEY_STATE::KEY_IDLE && App->input->joy_left2 == KEY_STATE::KEY_IDLE)
			&& (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE && App->input->dpadRight2 == KEY_STATE::KEY_IDLE && App->input->joy_right2 == KEY_STATE::KEY_IDLE))
			current_animation = &idle;
		else if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft2 == KEY_STATE::KEY_REPEAT || App->input->joy_left2 == KEY_STATE::KEY_REPEAT)
			&& (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->dpadRight2 == KEY_STATE::KEY_REPEAT || App->input->joy_right2 == KEY_STATE::KEY_REPEAT))
			current_animation = &idle;
	}

	App->fonts->BlitText(App->background->posScoreX + 80, 10, font_score, "2up");

	if (videsP2 == 4) {
		App->fonts->BlitText(App->background->posScoreX + 80 + 20, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX + 80 + 10, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX + 80, 20, font_score, "&");
	}
	if (videsP2 == 3) {
		App->fonts->BlitText(App->background->posScoreX + 80 + 10, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX + 80, 20, font_score, "&");
	}
	if (videsP2 == 2) {
		App->fonts->BlitText(App->background->posScoreX + 80, 20, font_score, "&");
	}
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();


	App->render->Blit(graphics, PROTA2.x, PROTA2.y, &r);

	colPlayer2->SetPos(PROTA2.x, PROTA2.y);

	
	if (destroyed == true) {
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 4000)) {
			if (videsP2 > 0) {
				if (auxiliar_vidaP2 == 0) {
					current_animation = &pDamaged;
					PROTA2.x = SCREEN_WIDTH / 2 - PROTA2.w / 2;
					PROTA2.y = SCREEN_HEIGHT / 2 + 30;
					auxiliar_vidaP2 = 1;
				}
			} else if (App->player2->videsP2 <= 0) {
				if (App->player->videsP1 <= 0 && App->player->IsEnabled() == false) {
					App->background->CleanUp();
					App->player->CleanUp();
					App->enemies->CleanUp();
					App->player2->CleanUp();
					App->menuScreen->Enable();
					App->menuScreen->CridaMenu();
				}
			}
		}
		else
			current_animation = &pDead;
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 2000)) {
			potMoure2 = true;
		}
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
			if (App->player2->videsP2 <= 0) {
				if (App->player->videsP1 <= 0 && App->player->IsEnabled() == false) {
					App->background->CleanUp();
					App->player->CleanUp();
					App->enemies->CleanUp();
					App->player2->CleanUp();
					App->menuScreen->Enable();
					App->menuScreen->CridaMenu();
				}
			}
			else {
				destroyed = false;
				potMoure2 = true;
				App->bullet->powerUpLevelPlayer2 = 0;
			}
		}
	}

	if (App->player->IsEnabled() == false)
		App->background->CridaScoreGeneral();
	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp() {
	bool ret = true;

	App->textures->Unload(graphics);
	App->player2->Disable();
	App->fonts->UnLoad(font_score2);
	App->fonts->UnLoad(font_score);

	return ret;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if ((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT) && destroyed == false && App->player->GodMode == false) {
		videsP2--;
		//if (videsP2 <= 0) {
		//	if (App->player->videsP1 > 0) {
		//		App->player2->CleanUp();
		//	}
		//	else {

		//	}
		//}
		//else {
		App->bullet->missileUpLevelPlayer2 = 0;
		App->bullet->powerUpLevelPlayer2 = 0;
		App->bullet->powerUpTypePlayer2 = Vulkan;
		current_time = SDL_GetTicks() + 5000;
		current_animation = &pDead;
		current_animation->Reset();
		potMoure2 = false;
		destroyed = true;
		auxiliar_vidaP2 = 0;
	}
}
