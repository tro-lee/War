#include "pch.h"
#include "Bullet.h"
void Bullet::Init(UINT uid, int x, int y, int speedY, int speedX)
{
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uid, IMAGE_BITMAP, 30, 30, NULL);
	m_PosX = x;
	m_PosY = y;
	m_SpeedY = rand() % 3 + 5 + speedY;
	m_SpeedX = speedX / 100;
	m_Rect = { 0, 0, 20, 20 };
}

void Bullet::Update()
{
	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;
	m_Rect = { m_PosX, m_PosY, m_PosX + 20, m_PosY + 20 };
}

void Bullet::Draw(HDC hDC, HDC hMDC, int x, int y)
{
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, 20, 20, hMDC, 0, 0, 30, 30, RGB(0, 0, 0));
}