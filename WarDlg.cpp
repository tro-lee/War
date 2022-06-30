
// WarDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "War.h"
#include "WarDlg.h"
#include "Arrow.h"
#include "afxdialogex.h"
#include "EasySize.h"
#include "Admin.h"
#include "BAdmin.h"

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
	mapX = 1050;
	mapY = 900;
	
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
ON_WM_SYSKEYDOWN()
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
	::SetTimer(this->m_hWnd, 201, 5, NULL);//201号定时器（开始游戏界面）
	::SetTimer(this->m_hWnd, 203, 100, NULL);//203号定时器（我机飞机子弹）
	arrow.inint(IDB_BITMAP11, 400, 375);
	select = 0;
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

		if (point.y <= 375) {
			select = 0;
			arrow.aimY = 375;
		}
		else if (point.y >= 565) {
			select = 2;
			arrow.aimY = 565;
		}
		else {
			select = 1;
			arrow.aimY = 470;
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
			if (arrow.aimY > 375)
			{
				select--;
				arrow.aimY -= 95;
			}
		}
		if (nChar == 'S') {
			if (arrow.aimY < 565)
			{
				select++;
				arrow.aimY += 95;
			}
		}
		if (nChar == ' ') {
			arrow.fire = 1;
			::SetTimer(this->m_hWnd, 204, 2000, NULL);//三号定时器（我机飞机子弹）
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
		if (nChar == 'P') {
			stopState = !stopState;
			if(stopState) {
				stop();
			}
			else {
				start();
			}
		}
		if (nChar == 'K') {
			gameOver();
		}
	}
	//控制结束
	if (state == 2) {
		if (nChar == ' ') {
			state = 0;
			KillTimer(301);
			::SetTimer(this->m_hWnd, 201, 5, NULL);//201号定时器（开始游戏界面）
			::SetTimer(this->m_hWnd, 203, 100, NULL);//203号定时器（我机飞机子弹）
			arrow.inint(IDB_BITMAP11, 300, 375);

			arrow.bullets.clear();
			me.bullets.clear();
			bullets.clear();
			enemy.clear();
		}
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
//存档机制
void CWarDlg::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(state == 1 && nChar == 'P') {
		admin.save(me);
		admin.save(enemy);
		admin.save(credits, level);
	}
	CDialogEx::OnSysKeyDown(nChar, nRepCnt, nFlags);
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
	if (state == 0) {
		if (nIDEvent == 201) {
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
			::TransparentBlt(hMDC, mapX / 7, mapY / 9, 800, 600, hMDCS, 0, 0, 400, 300, RGB(0, 0, 0));
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
		if (nIDEvent == 203) {
			if (arrow.fire == 1) {
				arrow.aimX = mapX - 200;
				arrow.BulletFire(IDB_BITMAP5);
			}
		}

	}
	
	if (nIDEvent == 204) {
		KillTimer(201);
		KillTimer(203);
		KillTimer(204);
		state = 1;
		OnOperateStart();
		KillTimer(4);
	}

	//游戏界面
	if (state == 1) {
		if (nIDEvent == 101) {
			upDate();
			paint();
		}
		if (nIDEvent == 102) {
			crash();
			for (size_t i = 0; i < booms.size(); i++)
			{
				booms[i].setMove(booms[i].getMove() + 1);
			}
		}
		if (nIDEvent == 103) {
			me.BulletFire(IDB_BITMAP5);
		}
		if (nIDEvent == 501) {
			show = 1;
			KillTimer(501);
			::SetTimer(this->m_hWnd, 502, 2000, NULL);
		}
		if (nIDEvent == 502) {
			show = 0;
			KillTimer(502);
		}
	}

	//结束界面
	if (state == 2) {

		if (nIDEvent == 301) {
			//屏幕DC创建兼容内存DC
			HDC hDC = ::GetDC(this->m_hWnd);
			HDC hMDC = ::CreateCompatibleDC(hDC);
			//内存位图
			HBITMAP hBmp = ::CreateCompatibleBitmap(hDC, mapX, mapY);
			HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMDC, hBmp);
			//画背景(滚动)
			paintBG(hMDC, rollX, rollY);
			rollY = rollY - 4;
			if (rollY <= 0) rollY = mapY;

			HDC hMDCS = ::CreateCompatibleDC(hDC);
			HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP13, IMAGE_BITMAP, 0, 0, NULL);
			::SelectObject(hMDCS, hBmpMap);
			::TransparentBlt(hMDC, 50, mapY / 4, 400, 300, hMDCS, 0, 0, 1200, 500, RGB(1, 1, 1));
			//贴数字
			paintMath(hMDC, top, 450, mapY / 4 + 10);
			paintMath(hMDC, credits, 450, mapY / 4 + 170);

			::BitBlt(hDC, 0, 0, mapX, mapY, hMDC, 0, 0, SRCCOPY);
			::DeleteObject(hBmpMap);
			::ReleaseDC(this->m_hWnd, hDC);
			::DeleteDC(hMDCS);
			::DeleteDC(hMDC);
			::DeleteObject(hBmp);
			::DeleteObject(hOldBmp);
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
	if (select == 0) {
		init();
		credits = 0;
		level = 1;
		stopState = FALSE;
		::SetTimer(this->m_hWnd, 101, 5, NULL);//一号定时器（核心），用来计算我机和敌机位置和画图，
		::SetTimer(this->m_hWnd, 102, 5, NULL);//二号定时器（碰撞 爆炸）
		::SetTimer(this->m_hWnd, 103, 200, NULL);//三号定时器（发射子弹）
	}
	if (select == 1) {
		int a = admin.loadEnemy();
		for (size_t i = 0; i < a; i++)
		{
			CEnemy en;
			en.Init(IDB_BITMAP3, 0, rand() % 3 + 3, 1, 50, 50, FALSE, 0, 0);
			enemy.push_back(en);
		}
		admin.load(enemy);
		me.Init(IDB_BITMAP2, mapX / 2 + 100, mapY - 50);
		admin.load(me);
		admin.load(credits, level);

		stopState = FALSE;
		::SetTimer(this->m_hWnd, 101, 5, NULL);//一号定时器（核心），用来计算我机和敌机位置和画图，
		::SetTimer(this->m_hWnd, 102, 5, NULL);//二号定时器（碰撞 爆炸）
		::SetTimer(this->m_hWnd, 103, 200, NULL);//三号定时器（发射子弹）
	}
}
void CWarDlg::init() {
	me.Init(IDB_BITMAP2, mapX / 2 + 100, mapY - 100);
}
void CWarDlg::stop() {
	KillTimer(101);
	KillTimer(102);
	KillTimer(103);
}
void CWarDlg::start() {
	::SetTimer(this->m_hWnd, 101, 5, NULL);//一号定时器（核心），用来计算我机和敌机位置和画图，
	::SetTimer(this->m_hWnd, 102, 5, NULL);//二号定时器（碰撞 爆炸）
	::SetTimer(this->m_hWnd, 103, 200, NULL);//三号定时器（发射子弹）
}
void CWarDlg::gameOver() {
	//我机爆炸
	Boom b;
	b.Init(IDB_BITMAP6, me.GetPosX(), me.GetPosY());
	//把游戏界面关掉
	KillTimer(101);
	KillTimer(102);
	KillTimer(103);
	//开启结算页面
	state = 2;
	select = 0;
	//读写最高分

	CFileFind finder;
	BOOL bWorking = (bool)finder.FindFile("./top.txt");

	if (!bWorking) {
		CFile files;
		files.Open("./top.txt", CFile::modeCreate | CFile::modeWrite, NULL);
		CString c;
		c.Format("%d", credits);
		files.Write(c, c.GetLength());
		files.Close();
	}
	else {
		CFile file;
		file.Open("./top.txt", CFile::modeReadWrite, NULL);
		int len = file.GetLength();
		char* b1 = new char(len + 1);
		file.Read(b1, len);
		file.Close();
		top = _ttoi(_T(b1));
	}
	CString c;
	if (credits > top) {
		CFile::Remove("./top.txt");
		CFile files;
		files.Open("./top.txt", CFile::modeCreate | CFile::modeWrite, NULL);
		c.Format("%d", credits);
		files.Write(c, c.GetLength());
		files.Close();
		top = credits;
	}

	::SetTimer(this->m_hWnd, 301, 5, NULL);//301号定时器（画积分）
}

//线程1的更新机制 用来实时计算数值
void CWarDlg::upDate() {
	//敌机产生
	levelEnemy();
	
	//功能包产生
	bAdmin();
	
	//功能包计算
	for (size_t i = 0; i < badmins.size(); i++)
	{
		badmins[i].Update(mapY - rollY);
	}
	//我机计算
	me.Update();

	//我机子弹
	for (size_t j = 0; j < me.bullets.size(); j++)
	{
		CPoint   point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		if (me.bullets[j].GetPosY() > me.GetPosY() - 100) {
			me.bullets[j].setSpeedX((point.x - me.bullets[j].GetPosX()) / 300);
		}
		me.bullets[j].Update();
	}
	
	//敌机子弹
	for (size_t j = 0; j < bullets.size(); j++)
	{
		bullets[j].Update();
	}

	//敌机
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].Update(me.GetPosX() - enemy[i].GetPosX());
		levelBullet(enemy[i]);

		//根据血量判断精英
		if (rand() % 100 < 1) {
			if (enemy[i].hp > 100) {
				enemy[i].setSpeedY(15);
			}
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
	rollY = rollY - 3 + me.GetSpeedY();
	if (rollY <= 0) rollY = mapY;
	//画分数
	paintCredits(hMDC);
	//画本机(直接画)
	me.Draw(hMDC, me.GetPosX(), me.GetPosY());
	//画敌机(并随机产生)
	paintEnemy(hMDC);
	//画系统包
	paintAdmin(hMDC);
	//画子弹
	paintBullet(hMDC);
	//画爆炸
	paintBoom(hMDC);
	//画关卡
	paintMath(hMDC, level, 20, 50);
	//画数字
	if (show == 1) {
		paintEvent(hMDC);
	}
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
	::DeleteDC(hMDC);
}
void CWarDlg::paintAdmin(HDC hDC) {
	HDC hMDC = ::CreateCompatibleDC(hDC);
	//使用已经有的
	for (size_t i = 0; i < badmins.size(); i++)
	{
		badmins[i].Draw(hDC);
		//超界删除
		if (badmins[i].GetPosY() > 850) {
			badmins.erase(badmins.begin() + i);
		}
	}
	::DeleteDC(hMDC);
}
void CWarDlg::levelEnemy() {
	//关卡设计
	if (credits / 500 + 1 > level) {
		showWhat = "up";
		::SetTimer(this->m_hWnd, 501, 5, NULL);
		level = credits / 500 + 1;
	}
	
	int sym = 1;
	//随机正负
	if (rand() % 100 < 50) {
		sym = -1;
	}
	//第一种小普通飞机
	if (rand() % 500 < (level % 3 + 1) * (level % 5 + 1)) {//频率为第一关
		int size = 50 + sym * (rand() % 2) * 20 + (rand() % 2) * 20 + level; //尺寸中等
		int hp = size / 10? size / 10: 1 + level; //血量中等
		CEnemy a;
		if (rand() % 4 < 1) {
			a.Init(IDB_BITMAP3, 0, rand() % 2 + level, hp, size, size, FALSE, rand() % 1000, 0);
		}
		else if (rand() % 4 < 1) {
			a.Init(IDB_BITMAP21, 0, rand() % 2 + level, hp, size, size, FALSE, rand() % 1000, 0);
		}
		else if (rand() % 4 < 1) {
			a.Init(IDB_BITMAP22, 0, rand() % 2 + level, hp, size, size, FALSE, rand() % 1000, 0);
		}
		else {
			a.Init(IDB_BITMAP23, 0, rand() % 2 + level, hp, size, size, FALSE, rand() % 1000, 0);
		}
		enemy.push_back(a);
	}
	//第二种小黑U飞机
	if (rand() % 1500 < (level / 2 == 0? 3: 1) * (level / 5)) {
		int size = 80 - (rand() % 20);
		int spX = rand() % 5 + level * 2;
		CEnemy a;
		a.Init(IDB_BITMAP15, 0, spX, 2, size, spX, FALSE, rand() % 1000, 0);
		enemy.push_back(a);
	}
	//第三种小白飞机
	if (rand() % 2000 < (level / 3 == 0 ? 5: 1) * (level / 5)) {
		int size = 75 + (rand() % 2) * 40 + level * 3;
		int hp = size / 2;
		CEnemy a;
		a.Init(IDB_BITMAP16, 0, rand() % 2 + 1, hp, size, hp, FALSE, rand() % 1000, 0);
		enemy.push_back(a);
	}
	//精英飞机
	if (rand() % 2000 < (level / 3)) {
		int size = 75 + (rand() % 3) * 40 + level * 3;
		int hp = size;
		CEnemy a;
		if (rand() % 3 < 1) {
			a.Init(IDB_BITMAP18, 0, rand() % 2, hp, size, size, FALSE, rand() % 1000, 0);
		}
		else if (rand() % 3 < 1) {
			a.Init(IDB_BITMAP19, 0, rand() % 2, hp, size, size, FALSE, rand() % 1000, 0);
		}
		else {
			a.Init(IDB_BITMAP20, 0, rand() % 2, hp, size, size, FALSE, rand() % 1000, 0);
		}
		enemy.push_back(a);
	}
}
void CWarDlg::bAdmin() {
	//产生Save包
	if (rand() % 500 < 1) {
		BAdmin a;
		a.Init(IDB_BITMAP17, "save", rand() % 1000, 10);
		badmins.push_back(a);
	}
}
void CWarDlg::levelBullet(CEnemy a) {
	//时不时产生子弹
	if (rand() % 1000 < (level)) {
		Bullet b;
		b.Init(IDB_BITMAP5, a.GetPosX() + a.size / 2, a.GetPosY() + a.size, a.GetSpeedY(), me.GetPosX() - a.GetPosX());
		bullets.push_back(b);
	}
	if (rand() % 200 < (level)) {
		if (a.hp > 100) {
			Bullet b;
			b.Init(IDB_BITMAP5, a.GetPosX() + a.size / 2, a.GetPosY() + a.size, a.GetSpeedY(), me.GetPosX() - a.GetPosX());
			bullets.push_back(b);
		}
	}
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
void CWarDlg::paintEvent(HDC hDC) {
	if (showWhat == "save") {
		HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP24, IMAGE_BITMAP, 0, 0, NULL);
		HDC hMDC = ::CreateCompatibleDC(hDC);
		::SelectObject(hMDC, hBmpMap);
		::TransparentBlt(hDC, 0, 0, 1000, 800, hMDC, 0, 0, 1050, 800, RGB(0, 0, 0));
		::DeleteDC(hMDC);
		::DeleteObject(hBmpMap);
	}
	if (showWhat == "up") {
		HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP25, IMAGE_BITMAP, 0, 0, NULL);
		HDC hMDC = ::CreateCompatibleDC(hDC);
		::SelectObject(hMDC, hBmpMap);
		::TransparentBlt(hDC, 0, 0, 1000, 800, hMDC, 0, 0, 1000, 700, RGB(0, 0, 0));
		::DeleteDC(hMDC);
		::DeleteObject(hBmpMap);
	}
}
void CWarDlg::paintCredits(HDC hDC) {
	CString s;
	s.Format("积分%d", credits);
	SetTextColor(hDC, RGB(255, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	RECT a = { 0, 0, 100, 400};
	DrawText(hDC, s, s.GetLength(), &a,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}
void CWarDlg::paintMath(HDC hDC, int num, int x, int y) {
	CString a;
	a.Format("%d", num);
	int len = a.GetLength();
	
	for (size_t i = 0; i < len; i++)
	{
		HBITMAP hBmpMap = (HBITMAP)::LoadImage(::GetModuleHandle(NULL), (LPCSTR)IDB_BITMAP14, IMAGE_BITMAP, 0, 0, NULL);
		HDC hMDC = ::CreateCompatibleDC(hDC);
		::SelectObject(hMDC, hBmpMap);

		int j = a[i] - '0';
		
		::TransparentBlt(hDC, x + 75 * i, y, 75, 75, hMDC, 120 * j, 0, 120, 120, RGB(1, 1, 1));
		::DeleteDC(hMDC);
		::DeleteObject(hBmpMap);
	}
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
	//功能包撞飞机
	for (size_t i = 0; i < badmins.size(); i++)
	{
		if (judgeMe(&badmins[i].m_Rect)) {
			allAdmin(badmins[i].type);
			badmins.erase(badmins.begin() + i);
		}
	}
	//敌人撞子弹
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (judgeEnemy(enemy[i].m_Rect)) {
			Boom b;
			b.Init(IDB_BITMAP6, enemy[i].GetPosX() + enemy[i].size / 2, enemy[i].GetPosY() + enemy[i].size / 2);
			booms.push_back(b);

			enemy[i].hp--;
			if (enemy[i].hp == 0) {
				credits += enemy[i].credit;
				enemy.erase(enemy.begin() + i);
			}
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
		|| PtInRect(e, { me.GetPosX() + 25, me.GetPosY() })
		|| PtInRect(e, { me.GetPosX() + 25, me.GetPosY() + 50 })
		|| PtInRect(e, { me.GetPosX(), me.GetPosY() + 50 })
		|| PtInRect(e, { me.GetPosX() + 25, me.GetPosY() })
		) return TRUE;
	return FALSE;
}
void CWarDlg::allAdmin(CString a) {
	if (a == "save") {
		admin.save(me);
		admin.save(enemy);
		admin.save(credits, level);
		showWhat = "save";
		::SetTimer(this->m_hWnd, 501, 5, NULL);
	}
}

//废掉
void CWarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//UPDATE_EASYSIZE;
}

