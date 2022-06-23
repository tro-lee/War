#pragma once
#include "AnyThing.h"
#include <vector>
class CEnemy: public AnyThing
{
public:
	void Init(UINT uid);
	void Update(int speedX);
	void Draw(HDC hDC, HDC hMDC, int x, int y);
};

