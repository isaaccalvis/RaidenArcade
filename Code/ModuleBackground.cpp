#include <time.h>
#include <stdlib.h>

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
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleBullets.h"
#include "ModuleFonts.h"


#include "SDL\include\SDL_timer.h"
#define MAP_HEIGHT 5850

ModuleBackground::ModuleBackground(){
	ground.x = 352;
	ground.y = 0;
	ground.w = 352;
	ground.h = MAP_HEIGHT;// MAP_HEIGHT;

	background.x = 0;
	background.y = 0;
	background.w = 352;
	background.h = MAP_HEIGHT;

	ship.x = 420;
	ship.y = 6075;
	ship.w = 225;
	ship.h = 512;
}

ModuleBackground::~ModuleBackground(){}

bool ModuleBackground::Start(){
	bool ret = true;
	contadorAuxiliarBoss = 0;
	current_time = SDL_GetTicks() + 5000;
	posBackGround = -MAP_HEIGHT /*- ORIGINAL_CAMERA_HEIGHT*/;
	posShipIncial = 0;
	speedBackGround = 0.3f;
	controlador_Auxiliar_Background_1 = true;
	controlador_spawn_LightShooter = 0;
	controlador_spawn_BonusPlane = 0;
	controlador_spawn_box = 0;
	controlador_spawn_Turret = 0;
	currenTime_Asteroids = SDL_GetTicks() + 6000;
	controlador_spawn_Heavy_Turret = 0;
	controlador_spawn_Basic_Tank = 0;
	controlador_spawn_Light_Shooter_Lateral = 0;
	controlador_spawn_Diamond_Plane = 0;
	controlador_spawn_Heavy_Orange_Airship = 0;

	graphics = App->textures->Load("Sprites/TileMaps/Nivel_6_Tilemap.png");
	App->music->LoadMusic("Audio/Music/Stage_3-6.ogg");
	auxiliar_musica_boss = 0;
	srand(time(NULL));
	posScoreX = 150;
	return ret;
}

update_status ModuleBackground::Update() {

	if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time)) {
		if (controlador_Auxiliar_Background_1 == true) {
			if (App->player->potMoure == false) {
				App->player->potMoure = true;
				App->bullet->Enable();
			}
			if (App->player2->potMoure2 == false) {
				App->player2->potMoure2 = true;
			}
			controlador_Auxiliar_Background_1 = false;
		}
		App->render->CleanRender();
		App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &background);
		App->enemies->CridaPrintSuperDown();
		App->render->fBlit(graphics, 0, posBackGround + SCREEN_HEIGHT, &ground);
		if (posBackGround < -265) // AIXO S'HA DE CANVIAR AL VALOR FINAL DEL MAPA
			posBackGround += speedBackGround;
		if (auxiliar_musica_boss == 2) { // Animacio del prota pirant del mapa
			App->player->GodMode = true;
			if (App->player->IsEnabled() == true) {
				App->player->potMoure = false;
				App->player->PROTA.y--;
			}
			if (App->player2->IsEnabled() == true) {
				App->player2->potMoure2 = false;
				App->player2->PROTA2.y--;
			}
			if (App->player->PROTA.y <= 0) {
				App->menuScreen->Enable();
				App->menuScreen->CridaMenu();
			}
		}
	}
	else {
		App->bullet->Disable();
		App->render->CleanRender();
		App->player->potMoure = false;
		App->player2->potMoure2 = false;
		App->render->fBlit(graphics, 0, SCREEN_HEIGHT - MAP_HEIGHT, &background);
		App->enemies->CridaPrintSuperDown();
		App->render->fBlit(graphics, 0, SCREEN_HEIGHT - MAP_HEIGHT, &ground);
		App->render->fBlit(graphics, 65, posShipIncial, &ship);
		if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 350)) {
			posShipIncial += 2;
			App->player->current_animation = &(App->player->Despegar3);
			App->player2->current_animation = &(App->player2->Despegar3);
		}
		else if (SDL_TICKS_PASSED(SDL_GetTicks(), current_time - 4000)) {
			App->player->current_animation = &(App->player->Despegar2);
			App->player2->current_animation = &(App->player2->Despegar2);
			posShipIncial += 1;
		}
		else {
			posShipIncial += 0;
			App->player->current_animation = &(App->player->Despegar1);
			App->player2->current_animation = &(App->player2->Despegar1);
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_STATE::KEY_DOWN && App->player->GodMode == true) {
		App->background->CleanUp();
		App->background2->CleanUp();
		App->player->CleanUp();
		App->player2->CleanUp();
		App->enemies->CleanUp();
		App->menuScreen->Enable();
		App->menuScreen->CridaMenu();

	}
	// ENEMIES 
	{

		// BONUS PLANE
		{
			if ((int)posBackGround == -2634 && controlador_spawn_BonusPlane < 4) {
				App->enemies->AddEnemy(BONUS_PLANE, 200, -30);
				controlador_spawn_BonusPlane++;
			}
			else if ((int)posBackGround == -3593 && controlador_spawn_BonusPlane < 3) {
				App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
				controlador_spawn_BonusPlane++;
			}
			else if ((int)posBackGround == -4327 && controlador_spawn_BonusPlane < 2) {
				App->enemies->AddEnemy(BONUS_PLANE, 149, -30);
				controlador_spawn_BonusPlane++;
			}
			else if ((int)posBackGround == -5004 && controlador_spawn_BonusPlane < 1) {
				App->enemies->AddEnemy(BONUS_PLANE, 133, -30);
				controlador_spawn_BonusPlane++;
			}
		}
		// BOX
		{
			// 5 ultimas en horizontal
			if ((int)posBackGround == -1957 && controlador_spawn_box < 18) {
				App->enemies->AddEnemy(BOX, 120, -20);
				controlador_spawn_box++;
			}
			else if ((int)posBackGround == -1958 && controlador_spawn_box < 17) {
				App->enemies->AddEnemy(BOX, 150, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -1959 && controlador_spawn_box < 16) { //CAIXA AMB BONUS
				App->enemies->AddEnemy(BOX, 180, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -1960 && controlador_spawn_box < 15) {
				App->enemies->AddEnemy(BOX, 210, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -1961 && controlador_spawn_box < 14) {
				App->enemies->AddEnemy(BOX, 240, -20);
				controlador_spawn_box++;
			}


			// 4 en vertical
			else if ((int)posBackGround == -2330 && controlador_spawn_box < 13) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -2360 && controlador_spawn_box < 12) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -2390 && controlador_spawn_box < 11) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -2420 && controlador_spawn_box < 10) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}

			// 3 antes del precipicio
			if ((int)posBackGround == -3525 && controlador_spawn_box < 9) {
				App->enemies->AddEnemy(BOX, 95, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3546 && controlador_spawn_box < 8) { //CAIXA AMB BONUS
				App->enemies->AddEnemy(BOX, 180, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3588 && controlador_spawn_box < 7) {
				App->enemies->AddEnemy(BOX, 265, -20);
				controlador_spawn_box++;
			}

			//Primeras 6

			else if ((int)posBackGround == -3756 && controlador_spawn_box < 6) {
				App->enemies->AddEnemy(BOX, 190, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3757 && controlador_spawn_box < 5) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3758 && controlador_spawn_box < 4) {
				App->enemies->AddEnemy(BOX, 270, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3806 && controlador_spawn_box < 3) {
				App->enemies->AddEnemy(BOX, 190, -20);
				controlador_spawn_box++;
			}

			else if ((int)posBackGround == -3807 && controlador_spawn_box < 2) {
				App->enemies->AddEnemy(BOX, 230, -20);
				controlador_spawn_box++;
			}
			else if ((int)posBackGround == -3808 && controlador_spawn_box < 1) {
				App->enemies->AddEnemy(BOX, 270, -20);
				controlador_spawn_box++;
			}
		}
		//Orange
		if ((int)posBackGround == -2184 && controlador_spawn_Heavy_Orange_Airship < 3) {
			App->enemies->AddEnemy(HEAVY_ORANGE_AIRSHIP, 30, 270);
			controlador_spawn_Heavy_Orange_Airship++;
		}

		else if ((int)posBackGround == -2728 && controlador_spawn_Heavy_Orange_Airship < 2) {
			App->enemies->AddEnemy(HEAVY_ORANGE_AIRSHIP, 50, 270);
			controlador_spawn_Heavy_Orange_Airship++;
		}
		else if ((int)posBackGround == -3528 && controlador_spawn_Heavy_Orange_Airship < 1) {
			App->enemies->AddEnemy(HEAVY_ORANGE_AIRSHIP, 10, 270);
			controlador_spawn_Heavy_Orange_Airship++;
		}

		//DiamondPlane
		if ((int)posBackGround == -1008 && controlador_spawn_Diamond_Plane < 5) {
			App->enemies->AddEnemy(DIAMOND_PLANE, 0, -30);
			controlador_spawn_Diamond_Plane++;
		}

		else if ((int)posBackGround == -1009 && controlador_spawn_Diamond_Plane < 4) {
			App->enemies->AddEnemy(DIAMOND_PLANE, 100, -30);
			controlador_spawn_Diamond_Plane++;
		}

		else if ((int)posBackGround == -1010 && controlador_spawn_Diamond_Plane < 3) {
			App->enemies->AddEnemy(DIAMOND_PLANE, 200, -30);
			controlador_spawn_Diamond_Plane++;
		}
		else if ((int)posBackGround == -1011 && controlador_spawn_Diamond_Plane < 2) {
			App->enemies->AddEnemy(DIAMOND_PLANE, 300, -30);
			controlador_spawn_Diamond_Plane++;
		}

		else if ((int)posBackGround == -2988 && controlador_spawn_Diamond_Plane < 1) {
			App->enemies->AddEnemy(DIAMOND_PLANE, 200, -30);
			controlador_spawn_Diamond_Plane++;
		}
		// TURRET
		{

			if ((int)posBackGround == -1210 && controlador_spawn_Heavy_Turret < 6) {
				App->enemies->AddEnemy(HEAVY_TURRET, 210, -18);
				controlador_spawn_Heavy_Turret++;
			}
			else if ((int)posBackGround == -1234 && controlador_spawn_Heavy_Turret < 5) {
				App->enemies->AddEnemy(HEAVY_TURRET, 120, -18);
				controlador_spawn_Heavy_Turret++;
			}

			else if ((int)posBackGround == -1278 && controlador_spawn_Heavy_Turret < 4) {
				App->enemies->AddEnemy(HEAVY_TURRET, 290, -18);
				controlador_spawn_Heavy_Turret++;
			}
			else if ((int)posBackGround == -1284 && controlador_spawn_Heavy_Turret < 3) {
				App->enemies->AddEnemy(HEAVY_TURRET, 180, -18);
				controlador_spawn_Heavy_Turret++;
			}
			else if ((int)posBackGround == -1368 && controlador_spawn_Heavy_Turret < 2) {
				App->enemies->AddEnemy(HEAVY_TURRET, 250, -18);
				controlador_spawn_Heavy_Turret++;
			}

			else if ((int)posBackGround == -1445 && controlador_spawn_Heavy_Turret < 1) {
				App->enemies->AddEnemy(HEAVY_TURRET, 260, -18);
				controlador_spawn_Heavy_Turret++;
			}
		}

		// VTANK


		{
			if ((int)posBackGround == -3320 && controlador_spawn_vTank < 5) {
				App->enemies->AddEnemy(VTANK, 80, -18);
				controlador_spawn_vTank++;
			}
			else if ((int)posBackGround == -3350 && controlador_spawn_vTank < 4) {
				App->enemies->AddEnemy(VTANK, 150, -18);
				controlador_spawn_vTank++;
			}
			else if ((int)posBackGround == -3380 && controlador_spawn_vTank < 3) {
				App->enemies->AddEnemy(VTANK, 210, -18);
				controlador_spawn_vTank++;
			}

			// Dos mov. horizontal
			if ((int)posBackGround == -3866 && controlador_spawn_vTank < 2) {
				App->enemies->AddEnemy(VTANK, 240, -18);
				controlador_spawn_vTank++;
			}
			else if ((int)posBackGround == -3950 && controlador_spawn_vTank < 1) {
				App->enemies->AddEnemy(VTANK, 100, -18);
				controlador_spawn_vTank++;
			}
		}

		//Tank
		{

			if ((int)posBackGround == -2147 && controlador_spawn_Basic_Tank < 22) {//Diagonal adalt esquerra
				App->enemies->AddEnemy(BASIC_TANK, 100, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -2660 && controlador_spawn_Basic_Tank < 21) {//Estatic
				App->enemies->AddEnemy(BASIC_TANK, 100, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -2700 && controlador_spawn_Basic_Tank < 20) {//Una mica a la dreta
				App->enemies->AddEnemy(BASIC_TANK, 15, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -2740 && controlador_spawn_Basic_Tank < 19) { //Una mica a la dreta
				App->enemies->AddEnemy(BASIC_TANK, 15, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3000 && controlador_spawn_Basic_Tank < 18) { //Abaix a al edreta, i despres abaix esquerra
				App->enemies->AddEnemy(BASIC_TANK, 145, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3040 && controlador_spawn_Basic_Tank < 17) {//Abaix a al edreta, i despres abaix esquerra
				App->enemies->AddEnemy(BASIC_TANK, 145, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3080 && controlador_spawn_Basic_Tank < 16) {//Abaix a al edreta, i despres abaix esquerra
				App->enemies->AddEnemy(BASIC_TANK, 145, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3120 && controlador_spawn_Basic_Tank < 15) { //Abaix a al edreta, i despres abaix esquerra
				App->enemies->AddEnemy(BASIC_TANK, 145, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3500 && controlador_spawn_Basic_Tank < 14) { //Dreta
				App->enemies->AddEnemy(BASIC_TANK, 20, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3520 && controlador_spawn_Basic_Tank < 13) {//Dreta
				App->enemies->AddEnemy(BASIC_TANK, 20, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3560 && controlador_spawn_Basic_Tank < 12) { //Dreta
				App->enemies->AddEnemy(BASIC_TANK, 20, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3600 && controlador_spawn_Basic_Tank < 11) { //Dreta
				App->enemies->AddEnemy(BASIC_TANK, 20, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3650 && controlador_spawn_Basic_Tank < 10) {//Estatic
				App->enemies->AddEnemy(BASIC_TANK, 90, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3675 && controlador_spawn_Basic_Tank < 9) { //Estatic
				App->enemies->AddEnemy(BASIC_TANK, 60, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3700 && controlador_spawn_Basic_Tank < 8) { //Estatic
				App->enemies->AddEnemy(BASIC_TANK, 30, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3800 && controlador_spawn_Basic_Tank < 7) {//Estatic
				App->enemies->AddEnemy(BASIC_TANK, 90, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3825 && controlador_spawn_Basic_Tank < 6) { //Estatic
				App->enemies->AddEnemy(BASIC_TANK, 60, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -3850 && controlador_spawn_Basic_Tank < 5) { //Estatic
				App->enemies->AddEnemy(BASIC_TANK, 30, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -4025 && controlador_spawn_Basic_Tank < 4) {//Esquerra una mica i es para
				App->enemies->AddEnemy(BASIC_TANK, 30, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -4050 && controlador_spawn_Basic_Tank < 3) { //Esquerra una mica i es para
				App->enemies->AddEnemy(BASIC_TANK, 70, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -4075 && controlador_spawn_Basic_Tank < 2) { //Dreta una mica i es para
				App->enemies->AddEnemy(BASIC_TANK, 200, -30);
				controlador_spawn_Basic_Tank++;
			}
			else if ((int)posBackGround == -4100 && controlador_spawn_Basic_Tank < 1) { //Dreta una mica i es para
				App->enemies->AddEnemy(BASIC_TANK, 250, -30);
				controlador_spawn_Basic_Tank++;
			}

		}

		// SHOOTER
		{
			if ((int)posBackGround == -940 && controlador_spawn_Light_Shooter_Lateral < 20) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -980 && controlador_spawn_Light_Shooter_Lateral < 19) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1020 && controlador_spawn_Light_Shooter_Lateral < 18) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}

			if ((int)posBackGround == -1060 && controlador_spawn_Light_Shooter_Lateral < 17) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1100 && controlador_spawn_Light_Shooter_Lateral < 16) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1140 && controlador_spawn_Light_Shooter_Lateral < 15) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}

			else if ((int)posBackGround == -1240 && controlador_spawn_Light_Shooter_Lateral < 14) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1280 && controlador_spawn_Light_Shooter_Lateral < 13) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1320 && controlador_spawn_Light_Shooter_Lateral < 12) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1360 && controlador_spawn_Light_Shooter_Lateral < 11) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1400 && controlador_spawn_Light_Shooter_Lateral < 10) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -1440 && controlador_spawn_Light_Shooter_Lateral < 9) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2460 && controlador_spawn_Light_Shooter_Lateral < 8) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2480 && controlador_spawn_Light_Shooter_Lateral < 7) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2520 && controlador_spawn_Light_Shooter_Lateral < 6) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}

			else if ((int)posBackGround == -2560 && controlador_spawn_Light_Shooter_Lateral < 5) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2600 && controlador_spawn_Light_Shooter_Lateral < 4) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2640 && controlador_spawn_Light_Shooter_Lateral < 3) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 270, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}

			else if ((int)posBackGround == -2780 && controlador_spawn_Light_Shooter_Lateral < 2) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
			else if ((int)posBackGround == -2820 && controlador_spawn_Light_Shooter_Lateral < 1) {
				App->enemies->AddEnemy(LIGHT_SHOOTER_LATERAL, 50, -30);
				controlador_spawn_Light_Shooter_Lateral++;
			}
		}
	}
	
		if  (posBackGround < - 800) {
			if (currenTime_Asteroids < SDL_GetTicks()) {
				currenTime_Asteroids = SDL_GetTicks() + 800;
				int pos = rand() % SCREEN_WIDTH;
				App->enemies->AddEnemy(ASTEROID, pos, -30);
			}
		}

		if ((int)posBackGround >= -400 && auxiliar_musica_boss == 0) {
			App->enemies->AddEnemy(BOSS6_BASE, 71, 10);
			App->enemies->AddEnemy(BOSS6_BASE, 170, 60);
			App->music->LoadMusic("Audio/Music/Boss.ogg");
			auxiliar_musica_boss = 1;
			current_time_boss = SDL_GetTicks() + 50000;
		}
		if (auxiliar_musica_boss == 1) {
			if (current_time_boss < SDL_GetTicks() ||contadorAuxiliarBoss >= 2) {
				auxiliar_musica_boss = 2;
			}
			else {
				speedBackGround = 0;
			}
		}
	return UPDATE_CONTINUE;
}

void ModuleBackground::CridaScoreGeneral() {
	if (App->player2->IsEnabled() == true) {

	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT)) {}
	else{
		if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
			if (App->player2->distanciaPlayers > -198)
				if (App->render->camera.x < 0)
					posScoreX--;
		if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
			if (App->player2->distanciaPlayers < 198)
				if ((App->render->camera.x - App->render->camera.w) > -SCREEN_WIDTH * 3)
					posScoreX++;
	}
	if (((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft2 == KEY_STATE::KEY_REPEAT || App->input->joy_left2 == KEY_STATE::KEY_REPEAT)) && ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->dpadRight2 == KEY_STATE::KEY_REPEAT || App->input->joy_right2 == KEY_STATE::KEY_REPEAT))) {}
	else {
		if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft2 == KEY_STATE::KEY_REPEAT || App->input->joy_left2 == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
			if (App->player2->distanciaPlayers < 198)
				if (App->render->camera.x < 0)
					posScoreX--;

		if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->dpadRight2 == KEY_STATE::KEY_REPEAT || App->input->joy_right2 == KEY_STATE::KEY_REPEAT) && (App->player->potMoure == true || App->player2->potMoure2 == true))
			if (App->player2->distanciaPlayers > -198)
				if ((App->render->camera.x - App->render->camera.w) > -SCREEN_WIDTH * 3)
					posScoreX++;
	}
	}
	else {
		if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT)) {}
		else {
			if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->dpadLeft == KEY_STATE::KEY_REPEAT || App->input->joy_left == KEY_STATE::KEY_REPEAT) && App->player->potMoure == true)
				if (App->render->camera.x < 0)
					posScoreX--;

			if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || App->input->dpadRight == KEY_STATE::KEY_REPEAT || App->input->joy_right == KEY_STATE::KEY_REPEAT) && App->player->potMoure == true)
				if ((App->render->camera.x - App->render->camera.w) > -SCREEN_WIDTH * 3)
					posScoreX++;
		}
	}
	




	App->fonts->BlitText(posScoreX, 10, App->player->font_score, "hi-score");
	char str[10];
	if (App->player->puntuacioP1 > App->player2->puntuacioP2)
		sprintf_s(str, "%i", App->player->puntuacioP1);
	else
		sprintf_s(str, "%i", App->player2->puntuacioP2);
	App->fonts->BlitText(posScoreX, 25, App->player->font_score, str);
	sprintf_s(App->player->score_text, 10, "%7d", App->player->puntuacioP1);
}

bool ModuleBackground::CleanUp() {
	bool ret = true;
	App->textures->Unload(graphics);
	App->background->Disable();
	//App->music->UnloadMusic();
	App->fonts->UnLoad(App->player->font_score);

	return ret;
}