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
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		if (active[i] != nullptr){
			delete active[i];
			active[i] = nullptr;
		}
	}
	App->particles->Disable();
	return true;
}

update_status ModuleParticles::Update(){
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i){
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false){
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born){
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false){
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay){
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

void ModuleParticles::loadParticlesTextures() {
	graphics = App->textures->Load("Sprites/Player/Player_Bullets.png");
	bullet.anim.PushBack({ 138,288, 6,7 });
	bullet.anim.loop = true;
	bullet.anim.speed = 1;
}

Particle::Particle(){
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update(){
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.finishedAnimation())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}