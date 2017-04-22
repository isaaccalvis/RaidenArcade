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

ModulePlayer2::ModulePlayer2() {
	current_animation = NULL;

	PROTA2.x = 200;
	PROTA2.y = 220;
	PROTA2.w = 26;
	PROTA2.h = 30;

	idle.PushBack({ 308, 19, 24, 34 });
	idle.PushBack({ 308, 61, 24, 34 });
	idle.speed = 0.4;

	rightMov.PushBack({ 341,19,21,34 });
	rightMov.PushBack({ 341,61,21,34 });
	rightMov.PushBack({ 375,19,16,34 });
	rightMov.PushBack({ 375,61,16,34 });
	rightMov.loop = false;
	rightMov.speed = 0.4;

	leftMov.PushBack({ 278,19,21,34 });
	leftMov.PushBack({ 278,61,21,34 });
	leftMov.PushBack({ 244,19,21,34 });
	leftMov.PushBack({ 244,61,21,34 });
	leftMov.loop = false;
	leftMov.speed = 0.4;
}

ModulePlayer2::~ModulePlayer2() {}

bool ModulePlayer2::Start() {
	puntuacioP2 = 0;
	videsP2 = 3;
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Player/Players.png");
	App->player2->Enable();
	print("ca");
	colPlayer2 = App->collision->AddCollider(PROTA2, COLLIDER_PLAYER2, this);
	return ret;
}

update_status ModulePlayer2::Update() {
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && PROTA2.x < (SCREEN_WIDTH - PROTA2.w)) {
		PROTA2.x += speed;
		if (current_animation != &rightMov) {
			rightMov.Reset();
			current_animation = &rightMov;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && PROTA2.x > 0) {
		PROTA2.x -= speed;
		if (current_animation != &leftMov) {
			leftMov.Reset();
			current_animation = &leftMov;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && PROTA2.y > PROTA2.h) {
		PROTA2.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && PROTA2.y < SCREEN_HEIGHT) {
		PROTA2.y += speed;
	}

	// CORRECTOR DE LIMITS
	if (PROTA2.x < 0)
		PROTA2.x = 0;
	if (PROTA2.x >(SCREEN_WIDTH - PROTA2.w))
		PROTA2.x = SCREEN_WIDTH - PROTA2.w;
	if (PROTA2.y < PROTA2.h)
		PROTA2.y = PROTA2.h;
	if (PROTA2.y > SCREEN_HEIGHT)
		PROTA2.y = SCREEN_HEIGHT;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;
	else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		current_animation = &idle;
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, PROTA2.x, PROTA2.y, &r);

	colPlayer2->SetPos(PROTA2.x, PROTA2.y);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp() {
	bool ret = true;

	App->textures->Unload(graphics);
	App->player2->Disable();

	return ret;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_TYPE::COLLIDER_ENEMY)
		App->menuScreen->Enable();
}