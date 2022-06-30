#pragma once
#include "AnyThing.h"
#include "Bullet.h"
#include <vector>
class CMyRole: public AnyThing
{
private:
public:
	std::vector<Bullet> bullets;
	virtual void Init(UINT uiID, int x, int y);
	virtual void Update();
	void BulletFire(UINT uid);
	virtual void Draw(HDC hDC, int x, int y);
};

