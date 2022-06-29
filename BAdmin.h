#pragma once
#include "AnyThing.h"
class BAdmin: public AnyThing
{
public:
	CString type;
	void Init(UINT uiID, CString c, int x, int y);
	void Update(int x);
	void Draw(HDC hDC);
};

