#pragma once
#include "AnyThing.h"
#include <vector>
class CEnemy: public AnyThing
{
public:
	int hp;
	int size;
	int credit;
	BOOL boss;//0ΪС�֣�1Ϊboss
	void Init(UINT uid, int speedX, int speedY, int hp, int size, int c, BOOL a, int posX, int posY);
	void Update(int speedX);
	void Draw(HDC hDC, HDC hMDC, int x, int y);
};

