#include "pch.h"
#include "CEnemy.h"
#include "Bullet.h"

void CEnemy::Init(UINT uid)
{
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uid, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = rand() % 1000;
	m_PosY = 0;
	m_SpeedX = 0;
	m_SpeedY = rand() % 3 + 3;
	m_Rect = { 0, 0, 100, 100 };
}

void CEnemy::Update(int speedX)
{
	if(speedX % 3 != 0)
	m_SpeedX = speedX % 3;
	if (m_PosX < 0) { m_PosX = 0; };
	if (m_PosX > 1300) { m_PosX = 1300; };
	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;
	m_Rect = { m_PosX, m_PosY, m_PosX + 100, m_PosY + 100 };
}

void CEnemy::Draw(HDC hDC, HDC hMDC, int x, int y)
{
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, 100, 100, hMDC, 0, 0, 34, 34, RGB(0, 0, 0));
}