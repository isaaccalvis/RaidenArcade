#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "ModuleBackground2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenuScreen.h"
#include "ModuleMusic.h"
#include "p2Point.h"
#include "ModuleEnemies.h"

#define MAP_HEIGHT 3265

ModuleBackground::ModuleBackground(){
	ground.x = 352;
	ground.y = 0;
	ground.w = 353;
	ground.h = MAP_HEIGHT;

	background.x = 0;
	background.y = 0;
	background.w = 352;
	background.h = MAP_HEIGHT;
	//vacas
	{
	PosCow1.x = 100;
	PosCow1.y = 2210;

	cow1.PushBack({ 24,26,48,25 });			// Bien puestas
	cow1.PushBack({ 77,26,48,25 });
	cow1.speed = 0.02;


	PosCow2.x = 250;
	PosCow2.y = 2223;

	cow2.PushBack({ 24, 68, 25, 35 });		// Bien puestas
	cow2.PushBack({ 56, 68, 25, 35 });
	cow2.PushBack({ 89, 68, 25, 35 });
	cow2.speed = 0.03;


	PosCow3.x = 40;
	PosCow3.y = 2185;

	cow3.PushBack({ 24, 114, 36, 32 });		// Bien Puestas
	cow3.PushBack({ 69, 114, 36, 32 });
	cow3.speed = 0.04;


	PosCow4.x = 85;
	PosCow4.y = 2139;

	cow4.PushBack({ 24, 274, 102, 59 });	// Bien Puestas
	cow4.speed = 0.02;


	PosCow5.x = 160;
	PosCow5.y = 2200;

	cow5.PushBack({ 25, 235, 57, 27 });		// Bien puestas
	cow5.PushBack({ 87, 235, 57, 27 });
	cow5.speed = 0.02;


	PosCow6.x = 215;
	PosCow6.y = 2137;

	cow6.PushBack({ 24, 342, 55, 47 });		// Bien puestas
	cow6.PushBack({ 87, 342, 55, 57 });
	cow6.speed = 0.01;


	PosCowboys.x = 210;
	PosCowboys.y = 2240;

	cowboys.PushBack({ 37, 422, 14, 16 });		// Bien puestos, falta que se muevan a la izquierda
	cowboys.PushBack({ 54, 422, 14, 16 });
	cowboys.PushBack({ 37, 422, 14, 16 });
	cowboys.PushBack({ 72, 422, 14, 16 });
	cowboys.speed = 0.15;
}
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){
	bool ret = true;
	posBackGround = -MAP_HEIGHT /*- ORIGINAL_CAMERA_HEIGHT*/;
	speedBackGround = 0.3;
	controlador_spawn_LightShooter = 0;
	controlador_spawn_BonusPlane = 0;
	controlador_spawn_box = 0;
	controlador_spawn_Turret = 0;
	graphics = App->textures->Load("Sprites/TileMaps/Nivel_1_Tilemap.png");
	cows = App->textures->Load("Sprites/Extras/Cows.png");
	App->music->LoadMusic(MUSIC_LEVEL_1);
	App->background->Enable();
	return ret;
}

update_status ModuleBackground::Update() {

	{
		if ((int)posBackGround == -1610 && controlador_spawn_Turret < 4) {
			App->enemies->AddEnemy(TURRET, 320, 10);
			controlador_spawn_Turret++;
		}

		else if ((int)posBackGround == -1690 && controlador_spawn_Turret < 3) {
			App->enemies->AddEnemy(TURRET, 120, 10);
			controlador_spawn_Turret++;
		}
		else if ((int)posBackGround == -1740 && controlador_spawn_Turret < 2) {
			App->enemies->AddEnemy(TURRET, 50, 0);
			controlador_spawn_Turret++;
		}

		else if ((int)posBackGround == -1763 && controlador_spawn_Turret < 1) {
			App->enemies->AddEnemy(TURRET, 10, 0);
			controlador_spawn_Turret++;
		}
	}
	// LightShooter Spawns
	{
		if ((int)posBackGround == -835 && controlador_spawn_LightShooter < 45) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 211, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -845 && controlador_spawn_LightShooter < 44) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -853 && controlador_spawn_LightShooter < 43) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 265, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -881 && controlador_spawn_LightShooter < 42) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 218, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -895 && controlador_spawn_LightShooter < 41) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 86, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -906 && controlador_spawn_LightShooter < 40) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 204, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -933 && controlador_spawn_LightShooter < 39) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -943 && controlador_spawn_LightShooter < 38) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 265, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -953 && controlador_spawn_LightShooter < 37) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 211, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -960 && controlador_spawn_LightShooter < 36) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 102, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -979 && controlador_spawn_LightShooter < 35) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 169, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -980 && controlador_spawn_LightShooter < 34) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 134, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -984 && controlador_spawn_LightShooter < 33) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1007 && controlador_spawn_LightShooter < 32) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1018 && controlador_spawn_LightShooter < 31) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 118, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1022 && controlador_spawn_LightShooter < 30) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 227, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1050 && controlador_spawn_LightShooter < 29) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 195, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1456 && controlador_spawn_LightShooter < 28) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 265, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1460 && controlador_spawn_LightShooter < 27) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 210, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1488 && controlador_spawn_LightShooter < 26) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 265, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1496 && controlador_spawn_LightShooter < 25) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 200, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1501 && controlador_spawn_LightShooter < 24) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 265, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1778 && controlador_spawn_LightShooter < 23) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1781 && controlador_spawn_LightShooter < 22) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 165, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1788 && controlador_spawn_LightShooter < 21) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 210, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1790 && controlador_spawn_LightShooter < 20) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 133, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1809 && controlador_spawn_LightShooter < 19) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1811 && controlador_spawn_LightShooter < 18) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 102, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1819 && controlador_spawn_LightShooter < 17) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 203, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1824 && controlador_spawn_LightShooter < 16) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 267, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1828 && controlador_spawn_LightShooter < 15) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 234, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1854 && controlador_spawn_LightShooter < 14) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 242, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1859 && controlador_spawn_LightShooter < 13) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 195, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1872 && controlador_spawn_LightShooter < 12) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 200, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1882 && controlador_spawn_LightShooter < 11) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 266, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -1908 && controlador_spawn_LightShooter < 10) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 241, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2269 && controlador_spawn_LightShooter < 9) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 166, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2279 && controlador_spawn_LightShooter < 8) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 89, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2289 && controlador_spawn_LightShooter < 7) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 137, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2318 && controlador_spawn_LightShooter < 6) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 240, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2329 && controlador_spawn_LightShooter < 5) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 263, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2341 && controlador_spawn_LightShooter < 4) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 197, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2987 && controlador_spawn_LightShooter < 3) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 233, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -2996 && controlador_spawn_LightShooter < 2) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 250, -30);
			controlador_spawn_LightShooter++;
		}
		else if ((int)posBackGround == -3085 && controlador_spawn_LightShooter < 1) {
			App->enemies->AddEnemy(LIGHT_SHOOTER, 188, -30);
			controlador_spawn_LightShooter++;
		}

	}

	// BonusPlanes Spawns
	{
		if ((int)posBackGround == -690 && controlador_spawn_BonusPlane < 5) {
			App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
			controlador_spawn_BonusPlane++;
		}
		else if ((int)posBackGround == -1050 && controlador_spawn_BonusPlane < 4) {
			App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
			controlador_spawn_BonusPlane++;
		}
		else if ((int)posBackGround == -1689 && controlador_spawn_BonusPlane < 3) {
			App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
			controlador_spawn_BonusPlane++;
		}
		else if ((int)posBackGround == -2210 && controlador_spawn_BonusPlane < 2) {
			App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
			controlador_spawn_BonusPlane++;
		}
		else if ((int)posBackGround == -2932 && controlador_spawn_BonusPlane < 1) {
			App->enemies->AddEnemy(BONUS_PLANE, 133, -30);
			controlador_spawn_BonusPlane++;
		}
	}
	// Box
	{
		if ((int)posBackGround == -490 && controlador_spawn_box < 11) {
			App->enemies->AddEnemy(BOX, 50, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -520 && controlador_spawn_box < 10) {
			App->enemies->AddEnemy(BOX, 260, 0);
			controlador_spawn_box++;
		}


		else if ((int)posBackGround == -1590 && controlador_spawn_box < 9) {
			App->enemies->AddEnemy(BOX, 310, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -1603 && controlador_spawn_box < 8) {
			App->enemies->AddEnemy(BOX, 80, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2275 && controlador_spawn_box < 7) {
			App->enemies->AddEnemy(BOX, 70, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2542 && controlador_spawn_box < 6) {
			App->enemies->AddEnemy(BOX, 180, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2543 && controlador_spawn_box < 5) {
			App->enemies->AddEnemy(BOX, 210, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2578 && controlador_spawn_box < 4) {
			App->enemies->AddEnemy(BOX, 180, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2579 && controlador_spawn_box < 3) {
			App->enemies->AddEnemy(BOX, 210, 0);
			controlador_spawn_box++;
		}

		else if ((int)posBackGround == -2720 && controlador_spawn_box < 2) { //CAIXA AMB BONUS//
			App->enemies->AddEnemy(BOX, 100, 0);
			controlador_spawn_box++;
		}
		else if ((int)posBackGround == -2830 && controlador_spawn_box < 1) {
			App->enemies->AddEnemy(BOX, 90, 0);
			controlador_spawn_box++;
		}
	}
	App->render->CleanRender();
	App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
	App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
	posBackGround += speedBackGround;
	// vacas
	{
		// Vacas
		Animation* current_animation = &cow1;
		SDL_Rect r = current_animation->GetCurrentFrame();
		App->render->Blit(cows, PosCow1.x, posBackGround + PosCow1.y, &r);

		Animation* current_animation2 = &cow2;
		SDL_Rect r2 = current_animation2->GetCurrentFrame();
		App->render->Blit(cows, PosCow2.x, posBackGround + PosCow2.y, &r2);

		Animation* current_animation3 = &cow3;
		SDL_Rect r3 = current_animation3->GetCurrentFrame();
		App->render->Blit(cows, PosCow3.x, posBackGround + PosCow3.y, &r3);

		Animation* current_animation4 = &cow4;
		SDL_Rect r4 = current_animation4->GetCurrentFrame();
		App->render->Blit(cows, PosCow4.x, posBackGround + PosCow4.y, &r4);

		Animation* current_animation5 = &cow5;
		SDL_Rect r5 = current_animation5->GetCurrentFrame();
		App->render->Blit(cows, PosCow5.x, posBackGround + PosCow5.y, &r5);

		Animation* current_animation6 = &cow6;
		SDL_Rect r6 = current_animation6->GetCurrentFrame();
		App->render->Blit(cows, PosCow6.x, posBackGround + PosCow6.y, &r6);


		// Cowboys
		Animation* current_animation7 = &cowboys;
		SDL_Rect r7 = current_animation7->GetCurrentFrame();

		//PosCowboys.x -= 0.00000000000001;
		App->render->Blit(cows, PosCowboys.x, posBackGround + PosCowboys.y, &r7);
	}

	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, App->background2, 1);
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN) {
		App->menuScreen->Enable();
		App->menuScreen->CridaMenu();
	}

	return UPDATE_CONTINUE;
}

bool ModuleBackground::CleanUp() {
	bool ret = true;
	App->textures->Unload(graphics);
	App->textures->Unload(cows);
	App->background->Disable();
	App->music->UnloadMusic(MUSIC_LEVEL_1);
	
	return ret;
}