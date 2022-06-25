#pragma once
#include "AnyThing.h"
#include "Bullet.h"
#include <vector>
class Arrow : public AnyThing
{
public:
	std::vector<Bullet> bullets;
	void BulletFire(UINT uid);
	int fire;
	int aimY;
	int aimX;
	void inint(UINT uid, int x, int y);
	void Draw(HDC hDC);
	void UpDate();
};

