#ifndef __HeavyTurret_H__
#define __HeavyTurret_H__

#include "Enemy.h"
#include "ModuleEnemies.h"

class HeavyTurret : public Enemy {
private:
	Animation HeavyTurret_Animation1;
	Animation HeavyTurret_Animation2;
	Animation HeavyTurret_Animation3;
	Animation HeavyTurret_Animation4;
	Animation HeavyTurret_Animation5;
	Animation HeavyTurret_Animation6;
	Animation HeavyTurret_Animation7;
	Animation HeavyTurret_Animation8;
	Animation HeavyTurret_Animation9;
	Animation HeavyTurret_Animation10;
	Animation HeavyTurret_Animation11;
	Animation HeavyTurret_Animation12;
	Animation HeavyTurret_Animation13;
	Animation HeavyTurret_Animation14;
	Animation HeavyTurret_Animation15;
	Animation HeavyTurret_Animation16;
	Animation HeavyTurret_Death;

	int estat;
	int current_time;
	bool dispara;
public:
	HeavyTurret(int x, int y);
	~HeavyTurret() {}
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
	float rectaY;
	float rectaX;
};
#endif