#include "pch.h"
#include "CMyRole.h"

void CMyRole::Init(UINT uiID, int x, int y)
{
	uid = uiID;
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uiID, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = x;
	m_PosY = y;
	m_SpeedX = 0;
	m_SpeedY = 0;
	m_Rect = { 0, 0, 50, 100};
}

void CMyRole::Update()
{
	if (m_PosX < 0) { m_PosX = 0; };
	if (m_PosX > 1300) { m_PosX = 1300; };
	if (m_PosY < 100) { m_PosY = 100; };
	if (m_PosY > 1100) { m_PosY = 1100; };
	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;
	m_Rect = { m_PosX, m_PosY, m_PosX + 50, m_PosY + 100 };
}

void CMyRole::Draw(HDC hDC, int x, int y)
{
	HDC hMDC = ::CreateCompatibleDC(hDC);
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, 50, 100, hMDC, 0, 0, 100, 220, RGB(0, 0, 0));
	::DeleteDC(hMDC);
}

void CMyRole::BulletFire(UINT uid) {
	Bullet a;
	a.Init(uid, m_PosX + 18, m_PosY - 10, -7, 0);
	bullets.push_back(a);

	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].GetPosY() <= 0) {
			bullets.erase(bullets.begin() + i);
		}
		bullets[i].m_SpeedY--;
	}
}
