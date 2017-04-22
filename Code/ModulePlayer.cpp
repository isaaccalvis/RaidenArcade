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

ModulePlayer::ModulePlayer(){
	current_animation = NULL;
	PROTA.w = 24;
	PROTA.h = 29;

	idle.PushBack({ 84, 19, 24, 34 });
	idle.PushBack({ 84, 61, 24, 34 });
	idle.speed = 0.4;

	rightMov.PushBack({ 117,19,21,34 });
	rightMov.PushBack({ 117,61,21,34 });
	rightMov.PushBack({ 151,19,16,34 });
	rightMov.PushBack({ 151,61,16,34 });
	rightMov.loop = false;
	rightMov.speed = 0.4;

	leftMov.PushBack({ 52,19,24,34 });
	leftMov.PushBack({ 52,61,24,34 });
	leftMov.PushBack({ 18,19,24,34 });
	leftMov.PushBack({ 18,61,24,34 });
	leftMov.loop = false;
	leftMov.speed = 0.4;
}

ModulePlayer::~ModulePlayer(){}


bool ModulePlayer::Start(){
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
		PROTA.x = 50;
		PROTA.y = SCREEN_HEIGHT / 2;
	}
	graphics = App->textures->Load("Sprites/Player/Players.png");
	colPlayer1 = App->collision->AddCollider(PROTA, COLLIDER_PLAYER, this);
	return ret;
}

update_status ModulePlayer::Update(){

	int speed = 2;
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
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && PROTA.y > 0) {
		PROTA.y -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && PROTA.y < SCREEN_HEIGHT - PROTA.w) {
		PROTA.y += speed;
	}
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

	colPlayer1->SetPos(PROTA.x, PROTA.y);

	// POSIBLE CULPABLE DE TOT EM CAGON LA PUTA
		/// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, PROTA.x, PROTA.y, &r);
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp(){
	bool ret = true;
	
	App->textures->Unload(graphics);
	App->player->Disable();

	return ret;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_TYPE::COLLIDER_ENEMY)
		App->menuScreen->Enable();
}