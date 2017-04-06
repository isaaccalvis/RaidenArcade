#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include <iostream>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2() {
	current_animation = NULL;
	//position.x = 100;
	//position.y = 220;
	PROTA2.x = SCREEN_WIDTH / 2;
	PROTA2.y = SCREEN_HEIGHT / 2;
	PROTA2.w = 26;
	PROTA2.h = 30;

	idle.PushBack({ 307, 18, 26, 30 });

	//Moviment Dreta
	rightMov.PushBack({ 340,18,24,30 });
	rightMov.PushBack({ 374,18,24,30 });
	rightMov.loop = false;
	rightMov.speed = 0.1f;

	leftMov.PushBack({ 277,18,24,30 });
	leftMov.PushBack({ 248,18,24,30 });
	leftMov.loop = false;
	leftMov.speed = 0.1f;

}

ModulePlayer2::~ModulePlayer2() {}

bool ModulePlayer2::Start() {
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Player/Players.png");
	App->player2->Enable();
	return ret;
}

update_status ModulePlayer2::Update() {
	int speed = 1;

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

	std::cout << App->render->camera.y << " :: " << PROTA2.y << std::endl;
	std::cout << App->render->camera.x << " :: " << PROTA2.x << std::endl;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, PROTA2.x, PROTA2.y - r.h, &r);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");
	bool ret = true;
	App->textures->Unload(graphics);

	return ret;
}