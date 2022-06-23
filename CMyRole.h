#pragma once
#include "AnyThing.h"
#include "Bullet.h"
#include <vector>
class CMyRole: public AnyThing
{
private:
public:
	std::vector<Bullet> bullets;
	void Init(UINT uiID, int x, int y);
	void Update();
	void BulletFire(UINT uid);
	void Draw(HDC hDC, int x, int y);
};

