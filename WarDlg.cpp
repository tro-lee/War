
// WarDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "War.h"
#include "WarDlg.h"
#include "Arrow.h"
#include "afxdialogex.h"
#include "EasySize.h"

//BEGIN_EASYSIZE_MAP(CWarDlg)
//	EASYSIZE(IDD_WAR_DIALOG, ES_KEEPSIZE, ES_KEEPSIZE, ES_KEEPSIZE, ES_KEEPSIZE, 0)
//END_EASYSIZE_MAP

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWarDlg 对话框



CWarDlg::CWarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	rollX = 0;
	rollY = 0;
	mapX = 1500;
	mapY = 1200;
	
	state = 0;
}

void CWarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWarDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, &CWarDlg::OnHelpAbout)
//	ON_COMMAND(ID_OPERATE_BITMAP, &CWarDlg::OnOperateBitmap)
//	ON_COMMAND(ID_OPERATE_TRANSPAREN2, &CWarDlg::OnOperateTransparen2)
//	ON_COMMAND(ID_OPERATE_TRANSPARENT1, &CWarDlg::OnOperateTransparent1)
//	ON_COMMAND(ID_OPERATE_TRANSPARENT3, &CWarDlg::OnOperateTransparent3)
ON_WM_KEYDOWN()
ON_WM_LBUTTONDOWN()
ON_COMMAND(ID_OPERATE_START, &CWarDlg::OnOperateStart)
ON_WM_TIMER()
ON_WM_KEYUP()
ON_WM_SIZE()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CWarDlg 消息处理程序

BOOL CWarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 将“关于...”菜单项添加到系统菜单中。

// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	//INIT_EASYSIZE;
	//GetWindowRect(rect);
	//point = rect.BottomRight();
	::SetTimer(this->m_hWnd, 204, 5, NULL);//204号定时器（开始游戏界面）
	::SetTimer(this->m_hWnd, 3, 100, NULL);//3号定时器（我机飞机子弹）
	arrow.inint(IDB_BITMAP11, 400, 475);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWarDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWarDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}

//鼠标移动
void CWarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (state == 0 && arrow.fire == 0) {
		arrow.aimX = point.x;
		if (arrow.aimX >= 1200) {
			arrow.aimX = 1200;
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


//按键设置
void CWarDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//控制箭头
	if (state == 0 && arrow.fire == 0) {
		if (nChar == 'W') {
			if(arrow.aimY > 475)
			arrow.aimY -= 130;
		}
		if (nChar == 'S') {
			if(arrow.aimY < 735)
			arrow.aimY += 130;
		}
		if (nChar == ' ') {
			arrow.fire = 1;
			::SetTimer(this->m_hWnd, 4, 2000, NULL);//三号定时器（我机飞机子弹）
		}
	}
	//控制飞机
	if (state == 1) {
		if (nChar == 'W') {
			me.setSpeedY(-2);
		}
		if (nChar == 'S') {
			me.setSpeedY(2);
		}
		if (nChar == 'A') {
			me.setSpeedX(-4);
		}
		if (nChar == 'D') {
			me.setSpeedX(4);
		}
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CWarDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == 'W') {
		me.setSpeedY(0);
	}
	else if (nChar == 'S') {
		me.setSpeedY(0);
	}
	else if (nChar == 'A') {
		me.setSpeedX(0);
	}
	else if (nChar == 'D') {
		me.setSpeedX(0);
	}
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}

//总体机制
/*
*	开始 开定时器，刷新绘制画面
*	结束 gameOver()
*/

void CWarDlg::OnTimer(UINT_PTR nIDEvent)
{
	//开始界面
	if (nIDEvent == 204) {
		//屏幕DC创建兼容内存DC
		HDC hDC = ::GetDC(this->m_hWnd);
		HDC hMDC = ::CreateCompatibleDC(hDC);
		//内存位图
		HBITMAP hBmp = ::CreateCompatibleBitmap(hDC, mapX, mapY);
		HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMDC, hBmp);
		//画背景(滚动)
		paintBG(hMDC, rollX, rollY);
		rollY = rollY - 5;
		if (rollY <= 0) rollY = mapY;

		arrow.UpDate();
		arrow.Draw(hMDC);

		//画界面（滚动）
		HDC hMDCS = ::CreateCompatibleDC(hDC);
		HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP10, IMAGE_BITMAP, 0, 0, NULL);
		::SelectObject(hMDCS, hBmpMap);
		::TransparentBlt(hMDC, 200, 100, 1000, 800, hMDCS, 0, 0, 400, 300, RGB(0, 0, 0));
		//画子弹(成功后)
		HDC hMDCB = ::CreateCompatibleDC(hDC);
		for (size_t i = 0; i < arrow.bullets.size(); i++)
		{
			arrow.bullets[i].Draw(hMDC, hMDCB, arrow.bullets[i].GetPosX(), arrow.bullets[i].GetPosY());
		}

		::BitBlt(hDC, 0, 0, mapX, mapY, hMDC, 0, 0, SRCCOPY);
		::DeleteObject(hBmpMap);
		::ReleaseDC(this->m_hWnd, hDC);
		::DeleteDC(hMDCS);
		::DeleteDC(hMDCB);
		::DeleteDC(hMDC);
		::DeleteObject(hBmp);
		::DeleteObject(hOldBmp);
	}
	
	if (nIDEvent == 3) {
		if (arrow.fire == 1) {
			arrow.aimX = 1100;
			arrow.BulletFire(IDB_BITMAP5);
		}
	}

	if (nIDEvent == 4) {
		KillTimer(3);
		KillTimer(204);
		state = 1;
		OnOperateStart();
		KillTimer(4);
	}

	//游戏界面
	if (state == 1) {
		if (nIDEvent == 1) {
			upDate();
			paint();
		}
		if (nIDEvent == 2) {
			crash();
			for (size_t i = 0; i < booms.size(); i++)
			{
				booms[i].setMove(booms[i].getMove() + 1);
			}
		}
		if (nIDEvent == 5) {
			me.BulletFire(IDB_BITMAP5);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CWarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//OnOperateStart();
}

void CWarDlg::OnOperateStart()
{
	// TODO: 在此添加命令处理程序代码
	init();
	credits = 0;
	::SetTimer(this->m_hWnd, 1, 5, NULL);//一号定时器（核心），用来计算我机和敌机位置和画图，
	::SetTimer(this->m_hWnd, 2, 5, NULL);//二号定时器（碰撞 爆炸）
	::SetTimer(this->m_hWnd, 4, 5, NULL);//四号定时器（显示）
	::SetTimer(this->m_hWnd, 5, 100, NULL);//四号定时器 （发射子弹）
}
void CWarDlg::init() {
	me.Init(IDB_BITMAP2, mapX / 2 - 150, mapY - 200);
}

void CWarDlg::gameOver() {
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	//画出GAMEOVER
	HDC hdc = ::GetDC(this->m_hWnd);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	RECT a = { 0, 0, mapX,mapY };
	DrawText(hdc, _T("GAME OVER"), strlen("GAME OVER"), &a,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	Boom b;
	b.Init(IDB_BITMAP6, me.GetPosX(), me.GetPosY());
	HDC hMDC = ::CreateCompatibleDC(hdc);
	b.Draw(hdc, hMDC, me.GetPosX(), me.GetPosY());
	::DeleteDC(hMDC);
	::ReleaseDC(this->m_hWnd, hdc);
}

//线程1的更新机制 用来实时计算数值
void CWarDlg::upDate() {
	me.Update();
	for (size_t j = 0; j < me.bullets.size(); j++)
	{
		CPoint   point;
		GetCursorPos(&point);

		ScreenToClient(&point);

		if (me.bullets[j].GetPosY() > point.y) {
			me.bullets[j].setSpeedX((point.x - me.bullets[j].GetPosX()) / 300);
		}
		me.bullets[j].Update();
	}

	for (size_t j = 0; j < bullets.size(); j++)
	{
		bullets[j].Update();
	}
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].Update(me.GetPosX() - enemy[i].GetPosX());
		//时不时产生子弹
		if (rand() % 200 < 5) {
			Bullet b;
			b.Init(IDB_BITMAP5, enemy[i].GetPosX() + 25, enemy[i].GetPosY() + 25, enemy[i].GetSpeedY(), me.GetPosX() - enemy[i].GetPosX());
			bullets.push_back(b);
		}
	}
}

//线程1的绘制机制 用来实时画图
void CWarDlg::paint() {
	//屏幕DC创建兼容内存DC
	HDC hDC = ::GetDC(this->m_hWnd);
	HDC hMDC = ::CreateCompatibleDC(hDC);
	//内存位图
	HBITMAP hBmp = ::CreateCompatibleBitmap(hDC, mapX, mapY);
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMDC, hBmp);

	//画背景(滚动)
	paintBG(hMDC, rollX, rollY);
	rollY = rollY - 3 + me.GetSpeedY() * 2;
	if (rollY <= 0) rollY = mapY;
	//画分数
	paintCredits(hMDC);
	//画本机(直接画)
	me.Draw(hMDC, me.GetPosX(), me.GetPosY());
	//画敌机(并随机产生)
	paintEnemy(hMDC);
	//画子弹
	paintBullet(hMDC);
	//画爆炸
	paintBoom(hMDC);

	//最后绘制
	::BitBlt(hDC, 0, 0, mapX, mapY, hMDC, 0, 0, SRCCOPY);
	::ReleaseDC(this->m_hWnd, hDC);
	::DeleteDC(hMDC);
	::DeleteObject(hBmp);
	::DeleteObject(hOldBmp);
}
void CWarDlg::paintBoom(HDC hDC) {
	HDC hMDC = ::CreateCompatibleDC(hDC);
	//使用已经有的
	for (size_t i = 0; i < booms.size(); i++)
	{
		booms[i].Draw(hDC, hMDC, booms[i].GetPosX(), booms[i].GetPosY());
		//超界删除
		if (booms[i].getMove() > 6) {
			booms.erase(booms.begin() + i);
		}
	}
	::DeleteDC(hMDC);
}
void CWarDlg::paintEnemy(HDC hDC) {
	HDC hMDC = ::CreateCompatibleDC(hDC);
	//使用已经有的
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].Draw(hDC, hMDC, enemy[i].GetPosX(), enemy[i].GetPosY());
		//超界删除
		if (enemy[i].GetPosY() > mapY) {
			enemy.erase(enemy.begin() + i);
		}
	}
	//生成新的
	if (rand() % 500 < 5) {
		CEnemy a;
		a.Init(IDB_BITMAP3);
		enemy.push_back(a);
	}
	::DeleteDC(hMDC);
}
void CWarDlg::paintBullet(HDC hDC) {
	HDC hMDC = ::CreateCompatibleDC(hDC);
	//使用已经有的
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].Draw(hDC, hMDC, bullets[i].GetPosX(), bullets[i].GetPosY());
		if (bullets[i].GetPosY() > mapY) {
			bullets.erase(bullets.begin() + i);
		}
	}
	for (size_t i = 0; i < me.bullets.size(); i++)
	{
		me.bullets[i].Draw(hDC, hMDC, me.bullets[i].GetPosX(), me.bullets[i].GetPosY());
		if (me.bullets[i].GetPosY() < 10) {
			me.bullets.erase(me.bullets.begin() + i);
		}
	}
	::DeleteDC(hMDC);
}
void CWarDlg::paintBG(HDC hDC, int x, int y) {
	//创建位图并调用函数LoadImage装载图
	HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP4, IMAGE_BITMAP, 0, 0, NULL);
	//定义并创建一个内存设备环境DC，调用函数创建兼容DC
	HDC hMDC = ::CreateCompatibleDC(hDC);
	////调用函数SelectObject，将位图选入兼容内存设备环境DC
	::SelectObject(hMDC, hBmpMap);
	////调用BitBlt
	::BitBlt(hDC, 0, 0, mapX, mapY, hMDC, x, y, SRCCOPY);
	::DeleteDC(hMDC);
	::DeleteObject(hBmpMap);
}
void CWarDlg::paintCredits(HDC hDC) {
	CString s;
	s.Format("积分%d", credits);
	SetTextColor(hDC, RGB(255, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	RECT a = { 0, 0, 200, 100};
	DrawText(hDC, s, s.GetLength(), &a,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}

//线程2的碰撞机制
void CWarDlg::crash() {
	//敌人撞飞机
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (judgeMe(&enemy[i].m_Rect)) {
			gameOver();
			enemy.erase(enemy.begin() + i);
		}
	}
	//敌人撞子弹
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (judgeEnemy(enemy[i].m_Rect)) {
			Boom b;
			b.Init(IDB_BITMAP6, enemy[i].GetPosX(), enemy[i].GetPosY());
			booms.push_back(b);
			credits += 100;
			enemy.erase(enemy.begin() + i);
		}
	}
	//碰撞子弹
	for (size_t j = 0; j < bullets.size(); j++)
	{
		if (judgeBullet({ bullets[j].GetPosX(), bullets[j].GetPosY() })) {
			gameOver();
			bullets.erase(bullets.begin() + j);
		}
	}
}
BOOL CWarDlg::judgeEnemy(RECT r) {
	for (size_t i = 0; i < me.bullets.size(); i++)
	{
		POINT a = { me.bullets[i].GetPosX(), me.bullets[i].GetPosY() };
		if (PtInRect(&r, { a.x, a.y })
			|| PtInRect(&r, { a.x + 20, a.y + 20 })
			|| PtInRect(&r, { a.x, a.y + 20 })
			|| PtInRect(&r, { a.x + 20, a.y })
			) return TRUE;
	}
	return FALSE;
}
BOOL CWarDlg::judgeBullet(POINT a) {
	if (PtInRect(&me.m_Rect, a)
		|| PtInRect(&me.m_Rect, { a.x + 20, a.y + 20 })
		|| PtInRect(&me.m_Rect, { a.x, a.y + 20 })
		|| PtInRect(&me.m_Rect, { a.x + 20, a.y })
		) return TRUE;
	return FALSE;
}
BOOL CWarDlg::judgeMe(const RECT* e) {
	if (PtInRect(e, { me.GetPosX(), me.GetPosY()})
		|| PtInRect(e, { me.GetPosX() + 50, me.GetPosY() })
		|| PtInRect(e, { me.GetPosX() + 50, me.GetPosY() + 100 })
		|| PtInRect(e, { me.GetPosX(), me.GetPosY() + 100 })
		|| PtInRect(e, { me.GetPosX() + 50, me.GetPosY() })
		) return TRUE;
	return FALSE;
}

//废掉
void CWarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//UPDATE_EASYSIZE;
}
