#ifndef __Hoaming_Missile_H__
#define __Hoaming_Missile_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class Hoaming_Missile : public Enemy {
private:
	Animation Hoaming_Missile_Animation;

	Animation Hoaming_Missile_Animation1;
	Animation Hoaming_Missile_Animation2;
	Animation Hoaming_Missile_Animation3;
	Animation Hoaming_Missile_Animation4;
	Animation Hoaming_Missile_Animation5;
	Animation Hoaming_Missile_Animation6;
	Animation Hoaming_Missile_Animation7;
	Animation Hoaming_Missile_Animation8;
	Animation Hoaming_Missile_Animation9;
	Animation Hoaming_Missile_Animation10;
	Animation Hoaming_Missile_Animation11;
	Animation Hoaming_Missile_Animation12;
	Animation Hoaming_Missile_Animation13;
	Animation Hoaming_Missile_Animation14;
	Animation Hoaming_Missile_Animation15;
	Animation Hoaming_Missile_Animation16;


	int current_time;
	bool dispara;
public:
	Hoaming_Missile(int x, int y);
	~Hoaming_Missile() {}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
	int enemicApuntant;
	float dirX = 0;
	float dirY = 0;
};
#endif