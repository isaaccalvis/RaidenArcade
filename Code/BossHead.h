#ifndef __Boss_Head_H__
#define __Boss_Head_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class bossHead : public Enemy {
private:
	Animation bossHead_Animation1;
	Animation bossHead_Animation2;
	Animation bossHead_Animation3;
	Animation bossHead_Animation4;
	Animation bossHead_Animation5;
	Animation bossHead_Animation6;
	Animation bossHead_Animation7;
	Animation bossHead_Animation8;
	Animation bossHead_Animation9;
	int current_time;
	bool dispara;
public:
	iPoint angleDisparBoss;
	bossHead(int x, int y);
	~bossHead();
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif