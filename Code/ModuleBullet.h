#ifndef __ModuleBullet_H__
#define __ModuleBullet_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"



class ModuleBullet
{
public:
	ModuleBullet();
	void Update();
	void Fire(float startX, float startY, float xSpeed, float ySpeed);
	void Draw();

private:
	bool alive;
	float x, y;
	float xv, yv;
};



ModuleBullet::ModuleBullet() :
	alive(false), x(0), y(0), xv(0), yv(0)
{}

void ModuleBullet::Update()
{
	if (alive)
	{
		x += xv;
		y += yv;
	}
}

void ModuleBullet::Fire(float startX, float startY, float xSpeed, float ySpeed)
{
	x = startX;
	y = startY;
	xv = xSpeed;
	yv = ySpeed;
	alive = true;
}

void ModuleBullet::Draw()
{
	if (alive)
	{
		//do whatever drawing you need in here
	}
}



#endif // !__MODULEBULLET_H__

