#include "pch.h"
#include "CEnemy.h"
#include "Bullet.h"

void CEnemy::Init(UINT uidL, int speedX, int speedY, int h, int s, int c, BOOL b)
{
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uidL, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = rand() % 1000;
	m_PosY = 0;
	m_SpeedX = speedX;
	m_SpeedY = speedY;
	uid = uidL;

	hp = h;
	size = s;
	credit = c;
	boss = b;

	m_Rect = { 0, 0, size, size };
}

void CEnemy::Update(int speedX)
{
	if(speedX % 3 != 0)
	m_SpeedX = speedX % 3;
	if (m_PosX < 0) { m_PosX = 0; };
	if (m_PosX > 1300) { m_PosX = 1300; };
	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;
	m_Rect = { m_PosX, m_PosY, m_PosX + size, m_PosY + size };
}

void CEnemy::Draw(HDC hDC, HDC hMDC, int x, int y)
{
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, size, size, hMDC, 0, 0, 34, 34, RGB(0, 0, 0));
}