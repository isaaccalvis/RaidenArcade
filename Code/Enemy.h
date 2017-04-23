#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;
	int vida;
public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw();
	virtual void OnCollision(Collider* collider);
	int fase = 0;
};

#endif // __ENEMY_H__