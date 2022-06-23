#pragma once
#include "AnyThing.h"
class Bullet: public AnyThing
{
public:

	void Init(UINT uid, int x, int y, int speedY, int speedX);
	void Update();
	void Draw(HDC hDC, HDC hMDC, int x, int y);
};

