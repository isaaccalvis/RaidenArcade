#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (active[i] == nullptr){
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}


void ModuleParticles::loadParticlesTextures() {
	particles_sprites = App->textures->Load("Sprites/Extras/Particles_Sprite.png");
	bullet.anim.PushBack({ 138,327, 6,7 });
	bullet.anim.loop = true;
	bullet.anim.speed = 1;
	bullet.life = 1000;

	enemyBulletBasic.anim.PushBack({18,360, 6,5 });
	enemyBulletBasic.anim.PushBack({ 25,360, 6,5 });
	enemyBulletBasic.anim.PushBack({ 32,360, 6,5 });
	enemyBulletBasic.anim.loop = true;
	enemyBulletBasic.anim.speed = 0.3f;
	enemyBulletBasic.life = 1500;

	restOfBulletCollision.anim.PushBack({ 11, 21,  9,  9 });
	restOfBulletCollision.anim.PushBack({ 27, 21, 10,  7 });
	restOfBulletCollision.anim.PushBack({ 44, 17, 10, 11 });
	restOfBulletCollision.anim.PushBack({ 60, 15, 12, 12 });
	restOfBulletCollision.anim.loop = false;
	restOfBulletCollision.anim.speed = 0.9f;
	restOfBulletCollision.life = 100;


	LightExplosion.anim.PushBack({ 395, 229, 24, 22 });
	LightExplosion.anim.PushBack({ 425, 227, 28, 26 });
	LightExplosion.anim.PushBack({ 467, 229, 20, 18 });
	LightExplosion.anim.PushBack({ 493, 227, 24, 22 });
	LightExplosion.anim.PushBack({ 522, 226, 26, 24 });
	LightExplosion.anim.PushBack({ 555, 224, 30, 28 });
	LightExplosion.anim.PushBack({ 592, 223, 31, 30 });
	LightExplosion.anim.PushBack({ 630, 223, 32, 30 });
	LightExplosion.anim.PushBack({ 667, 222, 32, 30 });
	LightExplosion.anim.PushBack({ 704, 222, 32, 30 });
	LightExplosion.anim.PushBack({ 742, 222, 32, 30 });
	LightExplosion.anim.PushBack({ 781, 222, 32, 30 });
	LightExplosion.anim.PushBack({ 822, 221, 32, 30 });
	LightExplosion.anim.PushBack({ 863, 222, 32, 30 });
	LightExplosion.anim.PushBack({ 910, 224, 18, 26 });
	LightExplosion.anim.PushBack({ 938, 210,  6, 14 });
	LightExplosion.anim.loop = false;
	LightExplosion.anim.speed = 0.3f;
	LightExplosion.life = 300;

	HeavyExplosion.anim.PushBack({ 394, 184, 22, 20 });
	HeavyExplosion.anim.PushBack({ 426, 182, 26, 24 });
	HeavyExplosion.anim.PushBack({ 462, 185, 20, 18 });
	HeavyExplosion.anim.PushBack({ 492, 183, 26, 23 });
	HeavyExplosion.anim.PushBack({ 528, 181, 30, 27 });
	HeavyExplosion.anim.PushBack({ 570, 180, 31, 28 });
	HeavyExplosion.anim.PushBack({ 611, 180, 31, 28 });
	HeavyExplosion.anim.PushBack({ 659, 176, 33, 29 });
	HeavyExplosion.anim.PushBack({ 705, 178, 30, 28 });
	HeavyExplosion.anim.PushBack({ 750, 179, 27, 25 });
	HeavyExplosion.anim.loop = false;
	HeavyExplosion.anim.speed = 0.3f;
	HeavyExplosion.life = 300;

	LargeExplosion.anim.PushBack({ 397,319,20,18 });
	LargeExplosion.anim.PushBack({ 427,315,46,38 });
	LargeExplosion.anim.PushBack({ 483,312,54,44 });
	LargeExplosion.anim.PushBack({ 556,310,58,48 });
	LargeExplosion.anim.PushBack({ 622,308,62,52 });
	LargeExplosion.anim.PushBack({ 693,307,62,52 });
	LargeExplosion.anim.PushBack({ 763,304,64,56 });
	LargeExplosion.anim.PushBack({ 839,301,64,60 });
	LargeExplosion.anim.PushBack({ 922, 303, 72, 64 });
	LargeExplosion.anim.loop = false;
	LargeExplosion.anim.speed = 0.2f;
	LargeExplosion.life = 300;

}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (active[i] != nullptr && active[i]->collider == c1){
			if (c2->type == COLLIDER_TYPE::COLLIDER_ENEMY || c2->type == COLLIDER_TYPE::COLLIDER_OBJECT_COLLISION) {
				delete active[i];
				active[i] = nullptr;
			}
			break;
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

	if (life > 0){
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

	return ret;
}