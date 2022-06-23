#pragma once
#include "AnyThing.h"
class Boom: public AnyThing
{
private:
	int move;
public:
	int getMove() { return move; };
	void setMove(int a) { move = a; };
	void Init(UINT uid, int x, int y);
	void Draw(HDC hDC, HDC hMDC, int x, int y);
};

