
// WarDlg.h: 头文件
//

#pragma once
#include "CMyRole.h"
#include "CEnemy.h"
#include "Boom.h"
#include "Bullet.h"
#include "EasySize.h"
#include "Arrow.h"
#include "Admin.h"
#include "BAdmin.h"
#include "CMyRoleSign.h"
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
	std::vector<BAdmin> badmins;
	std::vector<CMyRoleSign> signs;
	Admin admin;
public:
	//CRect rect;
	//POINT point;
	CString showWhat;
	int mapSpeed;
	int show;
	int level;
	int select;
	int state;//0为开始界面, 1为启动, 4为启动中途
	BOOL stopState;
	int mapY;
	int mapX;
	int credits;
	int top;
	int rollX;
	int rollY;
	void stop();
	void start();
	void bAdmin();
	void allAdmin(CString a);//功能包实现
	void levelEnemy();
	void levelBullet(CEnemy a);
	void paintBG(HDC hdc, int x, int y);
	void paintEnemy(HDC hdc);
	void paintAdmin(HDC hdc);
	void paintBullet(HDC hdc);
	void paintCredits(HDC hdc);
	void paintBoom(HDC hdc);
	void paintMath(HDC hdc, int a, int x, int y);
	void paintEvent(HDC hdc);
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
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHelp32777();
};
