#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include <iostream>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(){
	current_animation = NULL;
	//position.x = 100;
	//position.y = 220;
	PROTA.x = SCREEN_WIDTH / 2;
	PROTA.y = SCREEN_HEIGHT / 2;
	PROTA.w = 26;
	PROTA.h = 30;

	idle.PushBack({83, 18, 26, 30});

	//Moviment Dreta
	rightMov.PushBack({ 115,18,24,30 });
	rightMov.PushBack({ 148,18,24,30 });
	rightMov.loop = false;
	rightMov.speed = 0.1f;

	leftMov.PushBack({ 52,18,24,30 });
	leftMov.PushBack({ 16,18,24,30 });
	leftMov.loop = false;
	leftMov.speed = 0.1f;

}

ModulePlayer::~ModulePlayer(){}

bool ModulePlayer::Start(){
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Player/Players.png");
	App->player->Enable();
	return ret;
}

update_status ModulePlayer::Update(){
	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && PROTA.x < (SCREEN_WIDTH - PROTA.w)){
		PROTA.x += speed;
		if (current_animation != &rightMov){
			rightMov.Reset();
			current_animation = &rightMov;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && PROTA.x > 0) {
		PROTA.x -= speed;
		if (current_animation != &leftMov){
			leftMov.Reset();
			current_animation = &leftMov;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && PROTA.y > PROTA.h) {
		PROTA.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && PROTA.y < SCREEN_HEIGHT) {
		PROTA.y += speed;
	}

	// CORRECTOR DE LIMITS
	if (PROTA.x < 0)
		PROTA.x = 0;
	if (PROTA.x > (SCREEN_WIDTH - PROTA.w))
		PROTA.x = SCREEN_WIDTH - PROTA.w;
	if (PROTA.y < PROTA.h)
		PROTA.y = PROTA.h;
	if (PROTA.y > SCREEN_HEIGHT)
		PROTA.y = SCREEN_HEIGHT;

	std::cout << App->render->camera.y  << " :: " << PROTA.y<< std::endl;
	std::cout << App->render->camera.x << " :: " << PROTA.x << std::endl;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;
	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		current_animation = &idle;

		// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, PROTA.x, PROTA.y - r.h, &r);
	

	// APAREIX / DESAPAREIX JUGADOR 2 (ES FA DESDE AQUI PERQUE SI FAS DISABLE DEL JUGADOR 2 NO ES POT FER SERVIR)
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
		if (jugador2Activat == true)
			jugador2Activat = false;
		else
			jugador2Activat = true;
	if (jugador2Activat == true)
		App->player2->Enable();
	else
		App->player2->Disable();

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	bool ret = true;
	App->textures->Unload(graphics);

	return ret;
}