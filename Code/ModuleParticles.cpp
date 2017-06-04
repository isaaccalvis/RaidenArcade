#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleBullets.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles(){}

bool ModuleParticles::Start(){
	App->particles->Enable();
	loadParticlesTextures();
	return true;
}

bool ModuleParticles::CleanUp(){
	LOG("Unloading particles");
	App->textures->Unload(particles_sprites);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (active[i] != nullptr){
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}

update_status ModuleParticles::Update() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false) {
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born) {
			App->render->Blit(particles_sprites, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false) {
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int desfaceSprite, accioReaccio reaccio){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (active[i] == nullptr){
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			if (reaccio == 0)
				p->reaccioXoc = DESTRUCCIO;
			else
				p->reaccioXoc = reaccio;
			p->position.x = x;
			p->position.y = y;
			if (desfaceSprite == 0)
				p->desfaseOriginal = App->bullet->desfaseSpriteDispar;
			else
				if (p->collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT || p->collider->type == COLLIDER_TYPE::COLLIDER_PLAYER2_SHOT)
					p->desfaseOriginal = desfaceSprite;
			if (collider_type != COLLIDER_NONE) {
				SDL_Rect r = p->anim.GetCurrentFrame();
				r.x = p->position.x;
				r.y = p->position.y;
				p->collider = App->collision->AddCollider(r, collider_type, this);
			}
			active[i] = p;
			break;
		}
	}
}


void ModuleParticles::loadParticlesTextures() {
	particles_sprites = App->textures->Load("Sprites/Extras/Particles_Sprite.png");

	bullet.anim.PushBack({ 138,327, 6,7 });
	bullet.anim.loop = false;
	bullet.anim.speed = 1;
	bullet.life = 1000;

	bullet3.anim.PushBack({ 136,141, 10,6 });
	bullet3.anim.loop = false;
	bullet3.anim.speed = 1;
	bullet3.life = 1000;

	bulletR.anim.PushBack({ 183,72, 16,10 });
	bulletR.anim.loop = false;
	bulletR.anim.speed = 1;
	bulletR.life = 1000;

	bulletL.anim.PushBack({ 81,72, 16,10 });
	bulletL.anim.loop = false;
	bulletL.anim.speed = 1;
	bulletL.life = 1000;

	laserLight.anim.PushBack({ 45, 321, 2, 15 });
	laserLight.anim.loop = false;
	laserLight.anim.speed = 1;
	laserLight.life = 1000;

	laserHeavy2s.anim.PushBack({ 39, 298, 14, 14 });
	laserHeavy2s.anim.loop = false;
	laserHeavy2s.anim.speed = 1;
	laserHeavy2s.life = 1000;

	laserHeavy3s.anim.PushBack({ 38, 223, 16, 15 });
	laserHeavy3s.anim.loop = false;
	laserHeavy3s.anim.speed = 1;
	laserHeavy3s.life = 1000;

	LaserBeamHeavy.anim.PushBack({ 37, 55, 17, 16 });
	LaserBeamHeavy.anim.loop = false;
	LaserBeamHeavy.anim.speed = 1;
	LaserBeamHeavy.life = 1000;

	enemyBulletBasic.anim.PushBack({ 18,360, 6,5 });
	enemyBulletBasic.anim.PushBack({ 25,360, 6,5 });
	enemyBulletBasic.anim.PushBack({ 32,360, 6,5 });
	enemyBulletBasic.anim.loop = true;
	enemyBulletBasic.anim.speed = 0.3f;
	enemyBulletBasic.life = 3000;

	restOfBulletCollision.anim.PushBack({ 11, 21,  9,  9 });
	restOfBulletCollision.anim.PushBack({ 27, 21, 10,  7 });
	restOfBulletCollision.anim.PushBack({ 44, 17, 10, 11 });
	restOfBulletCollision.anim.PushBack({ 60, 15, 12, 12 });
	restOfBulletCollision.anim.loop = false;
	restOfBulletCollision.anim.speed = 0.9f;
	restOfBulletCollision.life = 100;

	preBomb.anim.PushBack({ 225, 54, 8, 15 });
	preBomb.anim.PushBack({ 242, 54, 8, 15 });
	preBomb.anim.PushBack({ 225, 79, 8, 15 });
	preBomb.anim.PushBack({ 242, 79, 8, 15 });
	preBomb.anim.PushBack({ 259, 79, 8, 15 });
	preBomb.anim.PushBack({ 276, 79, 8, 15 });
	preBomb.anim.PushBack({ 292, 79, 8, 15 });
	preBomb.anim.PushBack({ 309, 79, 8, 15 });
	preBomb.anim.loop = false;
	preBomb.anim.speed = 0.2f;
	preBomb.life = 1000;	

	NuclearMissile.anim.PushBack({ 226, 127, 6, 16 });
	NuclearMissile.anim.PushBack({ 243, 127, 6, 16 });
	NuclearMissile.anim.loop = true;
	NuclearMissile.anim.speed = 0.3f;
	NuclearMissile.life = 1000;

	bomb.anim.PushBack({ 495, 635, 168, 168 });
	bomb.anim.PushBack({ 667, 635, 168, 168 });
	bomb.anim.PushBack({ 834, 635, 168, 168 });
	bomb.anim.loop = true;
	bomb.anim.speed = 0.3f;
	bomb.life = 1000;

	bombFantasma.anim.PushBack({ 735, 0, 168, 168 });
	bombFantasma.anim.loop = true;
	bombFantasma.anim.speed = 0.9f;
	bombFantasma.life = 200;

	LightExplosion.anim.PushBack({ 397,219,24,22 });
	LightExplosion.anim.PushBack({ 427, 217, 28, 26 });
	LightExplosion.anim.PushBack({ 469, 219, 20, 18 });
	LightExplosion.anim.PushBack({ 495, 217, 24, 22 });
	LightExplosion.anim.PushBack({ 524, 216, 26, 24 });
	LightExplosion.anim.PushBack({ 557, 214, 30, 28 });
	LightExplosion.anim.PushBack({ 594, 213, 31, 30 });
	LightExplosion.anim.PushBack({ 632, 213, 32, 30 });
	LightExplosion.anim.PushBack({ 706, 212, 32, 30 });
	LightExplosion.anim.PushBack({ 783, 212, 32, 30 });
	LightExplosion.anim.PushBack({ 824, 211, 32, 30 });
	LightExplosion.anim.PushBack({ 865, 212, 32, 30 });
	LightExplosion.anim.PushBack({ 912, 214, 18, 26 });
	LightExplosion.anim.PushBack({ 940, 220, 6, 14 });
	LightExplosion.anim.loop = false;
	LightExplosion.anim.speed = 0.3f;
	
	HeavyExplosion.anim.PushBack({ 398,174,22,21 });
	HeavyExplosion.anim.PushBack({ 428,172,26,24 });
	HeavyExplosion.anim.PushBack({ 463,175,20,18 });
	HeavyExplosion.anim.PushBack({ 492,172,25,22 });
	HeavyExplosion.anim.PushBack({ 522,170,28,26 });
	HeavyExplosion.anim.PushBack({ 553,170,30,27 });
	HeavyExplosion.anim.PushBack({ 585,170,31,29 });
	HeavyExplosion.anim.PushBack({ 617,169,32,29 });
	HeavyExplosion.anim.PushBack({ 649,170,30,27 });
	HeavyExplosion.anim.PushBack({ 683,171,27,26 });
	HeavyExplosion.anim.loop = false;
	HeavyExplosion.anim.speed = 0.3f;
	HeavyExplosion.life = 300;
	
	LargeExplosion.anim.PushBack({ 436,316,20,18 });
	LargeExplosion.anim.PushBack({ 488, 306, 46, 38 });
	LargeExplosion.anim.PushBack({ 548, 303, 54, 44 });
	LargeExplosion.anim.PushBack({ 610, 301, 59, 48 });
	LargeExplosion.anim.PushBack({ 672, 299, 62, 52 });
	LargeExplosion.anim.PushBack({ 736, 299, 62, 52 });
	LargeExplosion.anim.PushBack({ 799, 296, 64, 56 });
	LargeExplosion.anim.PushBack({ 862, 295, 65, 60 });
	LargeExplosion.anim.PushBack({ 927, 293, 68, 62 });
	LargeExplosion.anim.loop = false;
	LargeExplosion.anim.speed = 0.5f;
	LargeExplosion.life = 300;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		if (active[i] != nullptr && active[i]->collider == c1) {
			switch (active[i]->reaccioXoc) {
			case DESTRUCCIO:
				delete active[i];
				active[i] = nullptr;
				break;
			case SPAWN_LIGHT_EXPLOSION:
				AddParticle(App->particles->LightExplosion, active[i]->position.x, active[i]->position.y, COLLIDER_PLAYER_SHOT);
				AddParticle(App->particles->LightExplosion, active[i]->position.x, active[i]->position.y, COLLIDER_NONE);
				delete active[i];
				active[i] = nullptr;
				break;
			case SPAWN_LIGHT_EXPLOSION_P2:
				AddParticle(App->particles->LightExplosion, active[i]->position.x, active[i]->position.y, COLLIDER_PLAYER2_SHOT);
				AddParticle(App->particles->LightExplosion, active[i]->position.x, active[i]->position.y, COLLIDER_NONE);
				delete active[i];
				active[i] = nullptr;
				break;
			}
		}
	}
}
Particle::Particle(){
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle(){
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update(){
	bool ret = true;
	if (SDL_GetTicks() >= born) {
		if (life > 0) {
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (anim.finishedAnimation())
				ret = false;

		position.x += speed.x;
		position.y += speed.y;

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}
	else if (SDL_GetTicks() + 1000 >= born){ // he posat 1000 perque no s'executi sempre si el born es molt gran
		if (collider != nullptr) {
			if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {
				position.x = App->player->PROTA.x + App->player->PROTA.w / 2 - desfaseOriginal;
				position.y = App->player->PROTA.y;
			}
			else if (collider->type == COLLIDER_TYPE::COLLIDER_PLAYER2_SHOT) {
				position.x = App->player2->PROTA2.x + App->player2->PROTA2.w / 2 - desfaseOriginal;
				position.y = App->player2->PROTA2.y;
			}
		}
	}
	return ret;
}