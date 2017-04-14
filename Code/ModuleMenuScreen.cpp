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
	
	pantallaIniciAnimStatic.PushBack({ 0,0,223,255 });
	pantallaIniciAnimStatic.speed = 0.5f;
	pantallaIniciAnimStatic.loop = false;

	pantallaIniciAnim.PushBack({0,0,223,255});
	pantallaIniciAnim.PushBack({ 225,0,223,255 });
	pantallaIniciAnim.PushBack({ 450,0,223,255 });
	pantallaIniciAnim.PushBack({ 675,0,223,255 });
	pantallaIniciAnim.PushBack({ 0,257,223,255 });
	pantallaIniciAnim.PushBack({ 225,257,223,255 });
	pantallaIniciAnim.PushBack({ 450,257,223,255 });
	pantallaIniciAnim.PushBack({ 675,257,223,255 });
	pantallaIniciAnim.speed = 0.5f;
	pantallaIniciAnim.loop = false;

}
ModuleMenuScreen::~ModuleMenuScreen() {}

bool ModuleMenuScreen::Start() {
	MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
	App->menuScreen->Enable();
	current_animation = &pantallaIniciAnimStatic;
	return true;
}

bool ModuleMenuScreen::selectorScreen(MenuScreenNames name) {
	bool ret = true;
	switch (name) {
	case StartScreen:
		App->player->Disable();
		App->bullet->Disable();
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Loading_Screen.png");
	break;
	case GameOverScreen:
		App->player->Disable();
		App->bullet->Disable();
		App->render->MoveCameraToCenter();
		MenuScreenTexture = App->textures->Load("Sprites/MenuImages/Continue_Screen.png");
		current_animation = &pantallaIniciAnimStatic;
		App->music->CargarMusica(MUSICA_GAME_CONTINUE);
	break;
	}
	return ret;
}

update_status ModuleMenuScreen::Update() {
	App->render->CleanRender();
	App->render->Blit(MenuScreenTexture,59/*Aquest 59 s'ha de canviar per una funcio*/, 0, &MenuScreenRect);
	MenuScreenRect = current_animation->GetCurrentFrame();

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN) {
		current_animation = &pantallaIniciAnim;
		App->fade->FadeToBlack(this, App->background, 0.5f);
		App->player2->Disable();
		App->player2->jugador2Activat = false;
	}
	else if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		current_animation = &pantallaIniciAnim;
		App->fade->FadeToBlack(this, App->background, 0.5f);
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