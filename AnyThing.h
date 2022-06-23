#pragma once
class AnyThing
{
private:

public:
	HBITMAP m_hBmp; //装载图片
	int m_PosX, m_PosY; //坐标
	int m_SpeedX, m_SpeedY; //速度
	RECT m_Rect; //碰撞矩形
	int GetSpeedX() { return m_SpeedX; };
	void setSpeedX(int x) { m_SpeedX = x; };
	int GetSpeedY() { return m_SpeedY; };
	void setSpeedY(int y) { m_SpeedY = y; };
	int GetPosX() { return m_PosX; };
	void setPosX(int x) { m_PosX = x; };
	int GetPosY() { return m_PosY; };
	void setPosY(int y) { m_PosY = y; };
};

