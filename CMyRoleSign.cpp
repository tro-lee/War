#include "pch.h"
#include "CMyRoleSign.h"

void CMyRoleSign::Init(UINT uiID, int x, int y, int spX, int spY)
{
	move = 0;
	uid = uiID;
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uiID, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = x;
	m_PosY = y;
	m_SpeedX = spX;
	m_SpeedY = spY;
	m_Rect = { 0, 0, 25, 50 };
}

void CMyRoleSign::Update()
{
	move++;
	if (m_PosX < 0) { m_PosX = 0; };
	if (m_PosX > 1000) { m_PosX = 1000; };
	if (m_PosY < 100) { m_PosY = 100; };
	if (m_PosY > 800) { m_PosY = 800; };
	m_PosX += m_SpeedX;
	m_PosY += m_SpeedY;
	m_Rect = { m_PosX, m_PosY, m_PosX + 25, m_PosY + 50 };

}

void CMyRoleSign::Draw(HDC hDC, int x, int y)
{
	HDC hMDC = ::CreateCompatibleDC(hDC);
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, 25, 50, hMDC, 0, 0, 100, 220, RGB(0, 0, 0));
	::DeleteDC(hMDC);
}