
// WarDlg.h: 头文件
//

#pragma once
#include "CMyRole.h"
#include "CEnemy.h"
#include "Boom.h"
#include "Bullet.h"
#include "EasySize.h"
#include "Arrow.h"
#include <vector>

// CWarDlg 对话框
class CWarDlg : public CDialogEx
{
	//DECLARE_EASYSIZE
private:
	CMyRole me;
	Arrow arrow;
	std::vector<Boom> booms;
	std::vector<CEnemy> enemy;
	std::vector<Bullet> bullets;
public:
	//CRect rect;
	//POINT point;
	int state;//0为开始界面, 1为启动, 4为启动中途
	int mapY;
	int mapX;
	int credits;
	int showCredits;
	int top;
	int rollX;
	int rollY;
	void paintBG(HDC hdc, int x, int y);
	void paintEnemy(HDC hdc);
	void paintBullet(HDC hdc);
	void paintCredits(HDC hdc);
	void paintBoom(HDC hdc);
	void paintMath(HDC hdc, int a, int x, int y);
	void paint();
	void init();
	void upDate();
	void crash();
	void gameOver();
	BOOL judgeEnemy(RECT r);
	BOOL judgeMe(const RECT* a);
	BOOL judgeBullet(POINT a);
// 构造
public:
	CWarDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpAbout();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOperateStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
