#ifndef __Object_MissileUp_H__
#define __Object_MissileUp_H__

#include "Enemy.h"
#include "ModuleEnemies.h"
#include "Path.h"

enum MissileUp_State {
	NuclearM,
	HomingM
};

class Object_MissileUp : public Enemy {
private:
	Animation Object_PowerUp_Animation;
	Animation Object_PowerUp_Animation_Nuclear;
	Animation Object_PowerUp_Animation_Homing;

	int current_time;
	MissileUp_State MissileUpState;
	Path path;
	fPoint original_pos;

public:
	Object_MissileUp(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	void DrawDown();
};
#endif