#include "pch.h"
#include "BAdmin.h"

void BAdmin::Init(UINT uiID, CString c, int x, int y)
{
	uid = uiID;
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uiID, IMAGE_BITMAP, 0, 0, NULL);
	m_Rect = { 0, 0, 50, 50 };

	type = c;
	m_PosX = x;
	m_PosY = y;
}

void BAdmin::Update(int y)
{
	m_PosY = y;
	m_Rect = { m_PosX, m_PosY, m_PosX + 50, m_PosY + 50 };
}

void BAdmin::Draw(HDC hDC)
{
	HDC hMDC = ::CreateCompatibleDC(hDC);
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, m_PosX, m_PosY, 50, 50, hMDC, 0, 0, 225, 211, RGB(0, 0, 0));
	::DeleteDC(hMDC);
}