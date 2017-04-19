#include "Globals.h"
#include "Application.h"
#include "ModuleMenuScreen.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleBackGround2.h"
#include "ModuleBullets.h"
#include "ModulePlayer.h"
#include "ModuleMusic.h"
#include "Animation.h"

ModuleMenuScreen::ModuleMenuScreen() {
	MenuScreenRect.x = 0;
	MenuScreenRect.y = 0;
	MenuScreenRect.w = 223;
	MenuScreenRect.h = 255;
	
	MainMenu.PushBack({ 0,0,223,255 });
	MainMenu.speed = 0.5f;
	MainMenu.loop = false;

	GameOver.PushBack({ 0,0,223,255 });


	MainMenu.speed = 0.1f;
	MainMenu.loop = false;

	Transition.PushBack({ 675,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 225,257,223,255 });
	Transition.PushBack({ 675,0,223,255 });
	Transition.PushBack({ 450,0,223,255 });
	Transition.PushBack({ 225,0,223,255 });
	Transition.PushBack({ 0,0,223,255 });
	Transition.PushBack({0,0,223,255});
	Transition.PushBack({ 225,0,223,255 });
	Transition.PushBack({ 450,0,223,255 });
	Transition.PushBack({ 675,0,223,255 });
	Transition.PushBack({ 0,257,223,255 });
	Transition.PushBack({ 225,257,223,255 });
	Transition.PushBack({ 450,257,223,255 });
	Transition.PushBack({ 675,257,223,255 });
	Transition.speed = 0.5f;
	Transition.loop = false;

}
ModuleMenuScreen::~ModuleMenuScreen() {}

bool ModuleMenuScreen::Start() {
	MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Start_Screen.png");

	current_animation = &MainMenu;
	return true;
}

bool ModuleMenuScreen::selectorScreen(MenuScreenNames name) {
	bool ret = true;
	switch (name) {
	case Players_Screen:
		App->player->Disable();
		App->bullet->Disable();
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Players_Screen.png");
		current_animation = &MainMenu;

	break;
	case Game_Over_Screen:

		App->player->Disable();
		App->bullet->Disable();
		App->render->MoveCameraToCenter();
		
		MenuScreenGameOver = App->textures->Load("Sprites/MenuImages/Texture_Game_Over.png");
		current_animation = &GameOver;
		App->music->CargarMusica(MUSICA_GAME_CONTINUE);

			if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN) {

				//que heliga yes

			}

			if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN) {

				//que elija no
			}

		

		break;
	}

	return ret;
}

update_status ModuleMenuScreen::Update() {
	App->render->CleanRender();
	App->render->Blit(MenuScreenTexture,59/*Aquest 59 s'ha de canviar per una funcio*/, 0, &MenuScreenRect);
	MenuScreenRect = current_animation->GetCurrentFrame();
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
		current_animation = &Transition;
		App->menuScreen->Enable();
		App->menuScreen->selectorScreen(Players_Screen);
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN) {
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
		current_animation = &Transition;
		App->fade->FadeToBlack(this, App->background, 2.5f);
		App->player2->Disable();
		App->player2->jugador2Activat = false;
	}
	else if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
		current_animation = &Transition;
		App->fade->FadeToBlack(this, App->background, 2.5f);
		App->player2->Enable();
		App->player2->jugador2Activat = true;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMenuScreen::CleanUp() {
	bool ret = true;
	App->textures->Unload(MenuScreenTexture);
	App->menuScreen->Disable();
	return ret;
}