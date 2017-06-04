#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

enum accioReaccio {
	DESTRUCCIO = 0,
	SPAWN_LIGHT_EXPLOSION,
	SPAWN_LIGHT_EXPLOSION_P2
};

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	int desfaseOriginal;
	accioReaccio reaccioXoc;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void loadParticlesTextures();
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, int desfaseSprite = 0, accioReaccio reaccio = DESTRUCCIO);

private:
	Particle* active[MAX_ACTIVE_PARTICLES];

public:
	SDL_Texture* particles_sprites = nullptr;
	Particle bullet;
	Particle bullet3;
	Particle bulletR;
	Particle bulletL;
	Particle laserLight;
	Particle laserHeavy2s;
	Particle laserHeavy3s;
	Particle LaserBeamHeavy;
	Particle NuclearMissile;
	Particle HoamingMissileLight;
	Particle preBomb;
	Particle bomb;
	Particle bombFantasma;
	Particle enemyBulletBasic;
	Particle LightExplosion;
	Particle HeavyExplosion;
	Particle LargeExplosion;
	Particle restOfBulletCollision;
};

#endif