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

	//Check for joysticks


	return ret;
}

update_status ModulePlayer::Update(){
	int speed = 2;
	if (potMoure == true) {
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT) {
			if (PROTA.x < (SCREEN_WIDTH - PROTA.w))
				if (App->player2->IsEnabled() == true) {
					if (App->player2->distanciaPlayers < 198)
						PROTA.x += speed;
				}
				else {
					PROTA.x += speed;
				}
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &rightMov)
				current_animation = &rightMov2;
			if (current_animation != &rightMov && current_animation != &rightMov2) {
				rightMov.Reset();
				current_animation = &rightMov;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) {
			if (PROTA.x > (0))
				if (App->player2->IsEnabled() == true) {
					if (App->player2->distanciaPlayers > -198)
					PROTA.x -= speed;
				}
				else {
					PROTA.x -= speed;
				}
			if (current_animation->IntCurrentFrame() == 3 && current_animation == &leftMov)
				current_animation = &leftMov2;
			if (current_animation != &leftMov && current_animation != &leftMov2) {
				leftMov.Reset();
				current_animation = &leftMov;
			}
		}
		if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || App->input->dpadUp == KEY_STATE::KEY_REPEAT || App->input->joy_up == KEY_STATE::KEY_REPEAT) && PROTA.y > 0){
			PROTA.y -= speed;
		}
		if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->dpadDown == KEY_STATE::KEY_REPEAT || App->input->joy_down == KEY_STATE::KEY_REPEAT) && PROTA.y < SCREEN_HEIGHT - PROTA.w) {
			PROTA.y += speed;
		}
		if (GodMode == true) {
			if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(LIGHT_SHOOTER, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BASIC_TANK, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BONUS_PLANE, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(TURRET, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BOX, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(MEDAL, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(POWER_UP, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(MISSILE_UP, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BOSS6_HEAD, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(HEAVY_TURRET, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(HEAVY_ORANGE_AIRSHIP, PROTA.x, SCREEN_HEIGHT);
			if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(ASTEROID, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(DIAMOND_PLANE, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(VTANK, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BOSS6_BASE, PROTA.x, 0);
			if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT)
				App->enemies->AddEnemy(BOMB, PROTA.x, 0);
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

		if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->dpadLeft == KEY_STATE::KEY_IDLE && App->input->joy_left == KEY_STATE::KEY_IDLE)
			&& (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && App->input->dpadRight == KEY_STATE::KEY_IDLE && App->input->joy_right == KEY_STATE::KEY_IDLE))
			current_animation = &idle;
		else if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT)
			&& (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT))
			current_animation = &idle;
	}

	

	if (destroyed == true) 
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 4000)) {
			if (videsP1 > 0) {
				if (auxiliar_vida == 0) {
					current_animation = &pDamaged;
					PROTA.x = SCREEN_WIDTH / 2 - PROTA.w / 2;
					PROTA.y = SCREEN_HEIGHT / 2 + 30;
					auxiliar_vida = 1;
				}
			} else if (videsP1 <= 0) {
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
		else
			current_animation = &pDead;
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 2000)) {
			potMoure = true;
		}
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


	App->fonts->BlitText(App->background->posScoreX - 70, 10, font_score, "1up");
	if (videsP1 == 4) {
		App->fonts->BlitText(App->background->posScoreX - 70 + 20, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX - 70 + 10, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX - 70, 20, font_score, "&");
	}
	else if (videsP1 == 3) {
		App->fonts->BlitText(App->background->posScoreX - 70 + 10, 20, font_score, "&");
		App->fonts->BlitText(App->background->posScoreX - 70, 20, font_score, "&");
	}
	else if (videsP1 == 2)
		App->fonts->BlitText(App->background->posScoreX - 70, 20, font_score, "&");

	colPlayer1->SetPos(PROTA.x, PROTA.y);
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
	if (c2->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT)
		print("ostia  ");
	if (auxiliar_vida == -1)
		print("ostia  auxiliar ");

	if (((c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT)) && destroyed == false && GodMode == false) {
		videsP1--;

		App->bullet->missileUpLevelPlayer1 = 0;
		App->bullet->powerUpLevelPlayer1 = 0;
		App->bullet->powerUpTypePlayer1 = Vulkan;

		current_time = SDL_GetTicks() + 5000;
		current_animation = &pDead;
		current_animation->Reset();
		potMoure = false;
		destroyed = true;
		auxiliar_vida = 0;
	}
}