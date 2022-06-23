#include "pch.h"
#include "Boom.h"

void Boom::Init(UINT uid, int x, int y)
{
	m_hBmp = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)uid, IMAGE_BITMAP, 0, 0, NULL);
	m_PosX = x;
	m_PosY = y;

	move = 1;
}

void Boom::Draw(HDC hDC, HDC hMDC, int x, int y)
{
	SelectObject(hMDC, m_hBmp);
	::TransparentBlt(hDC, x, y, 150, 150, hMDC, 65 * (move - 1), 0, 65, 65, RGB(0, 0, 0));
}