#ifndef __Enemy_Turret_H__
#define __Enemy_Turret_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Enemy_Turret : public Enemy {
private:
	Animation Enemy_Turret_Animation1;
	Animation Enemy_Turret_Animation2;
	Animation Enemy_Turret_Animation3;
	Animation Enemy_Turret_Animation4;
	Animation Enemy_Turret_Animation5;
	Animation Enemy_Turret_Animation6;
	Animation Enemy_Turret_Animation7;
	Animation Enemy_Turret_Animation8;
	Animation Enemy_Turret_Animation9;
	Animation Enemy_Turret_Animation10;
	Animation Enemy_Turret_Animation11;
	Animation Enemy_Turret_Animation12;
	Animation Enemy_Turret_Animation13;
	Animation Enemy_Turret_Animation14;
	Animation Enemy_Turret_Animation15;
	Animation Enemy_Turret_Animation16;
	int current_time;
	bool dispara;
public:
	Enemy_Turret(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown(/*SDL_Texture* sprites*/);
	float rectaY;
	float rectaX;
};
#endif