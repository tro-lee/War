#pragma once
#include "CMyRole.h"
class CMyRoleSign: public CMyRole
{
public:
	int move;
	void Init(UINT uiID, int x, int y, int spX, int spY);
	void Update();
	void Draw(HDC hDC, int x, int y);
};

