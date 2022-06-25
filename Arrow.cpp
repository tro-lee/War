#include "pch.h"
#include "Arrow.h"
#include "Bullet.h"

void Arrow::inint(UINT uid, int x, int y) {
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uid, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = x;
	m_PosY = y;
	
	aimX = x;
	aimY = y;

	fire = 0;
}

void Arrow::Draw(HDC hDC)
{
	HDC hMDC = ::CreateCompatibleDC(hDC);
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, m_PosX, m_PosY, 100, 100, hMDC, 0, 0, 60, 50, RGB(0, 0, 0));
	::DeleteDC(hMDC);
}

void Arrow::UpDate()
{
	m_SpeedX = (aimX - m_PosX) / 50;
	m_PosX += m_SpeedX;
	m_SpeedY = (aimY - m_PosY) / 10;
	m_PosY += m_SpeedY;
}

void Arrow::BulletFire(UINT uid) {
	Bullet a;
	a.Init(uid, m_PosX + 60, m_PosY + 30, 0, 0);
	bullets.push_back(a);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].setSpeedX(-50);
		bullets[i].Update();
		if (bullets[i].GetPosX() >= 1200) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

