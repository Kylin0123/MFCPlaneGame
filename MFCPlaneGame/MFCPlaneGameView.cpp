
// MFCPlaneGameView.cpp : CMFCPlaneGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCPlaneGame.h"
#endif

#include "MFCPlaneGameDoc.h"
#include "MFCPlaneGameView.h"
#include "GoodEndDlg.h"
#include "BadEndDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPlaneGameView

IMPLEMENT_DYNCREATE(CMFCPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CMFCPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCPlaneGameView 构造/析构

CMFCPlaneGameView::CMFCPlaneGameView()
{
	// TODO: 在此处添加构造代码

}

CMFCPlaneGameView::~CMFCPlaneGameView()
{
}

BOOL CMFCPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// 读取背景图片
void CMFCPlaneGameView::readBgPic(CDC* pDC)
{
	CPngImage image;
	CBitmap bitmap;
	image.Load(IDB_BG, AfxGetInstanceHandle());
	bitmap.Attach(image.Detach());
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);  // 创建与当前DC（pDC）兼容的DC
	dcCompatible.SelectObject(&bitmap);
	pDC->AlphaBlend(0,
		0,
		PLAY_WIDTH,
		PLAY_HEIGHT,
		&dcCompatible,
		0,
		0,
		852,
		480,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void CMFCPlaneGameView::readBtnPic(CDC * pDC, CRect * crect, UINT ID)
{
	CPngImage image;
	CBitmap bitmap;
	image.Load(ID, AfxGetInstanceHandle());
	bitmap.Attach(image.Detach());
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);  // 创建与当前DC（pDC）兼容的DC
	dcCompatible.SelectObject(&bitmap);
	pDC->AlphaBlend(crect->left,
		crect->top,
		crect->Width(),
		crect->Height(),
		&dcCompatible,
		0,
		0,
		300,
		41,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
	bitmap.DeleteObject();
	dcCompatible.DeleteDC();
}

void CMFCPlaneGameView::readPlayerState(CDC * pDC)
{
	pDC->Rectangle(0, 0, GAME_WIDTH, GAME_HEIGHT);
	pDC->Rectangle(0, 0, PLAY_WIDTH, PLAY_HEIGHT);
	CFont font;
	font.CreatePointFont(150, _T("微软雅黑"), pDC);
	pDC->SelectObject(&font);
	int lineHeight = 30;
	int left = PLAY_WIDTH;
	int top = PLAY_HEIGHT/10;
	pDC->TextOutW(left, top + lineHeight, _T("控制说明："));
	pDC->TextOutW(left, top + 1 * lineHeight, _T("暂停游戏:P"));
	pDC->TextOutW(left, top + 2 * lineHeight, _T("继续游戏：C"));
	pDC->TextOutW(left, top + 3 * lineHeight, _T("向上移动:W/鼠标操作"));
	pDC->TextOutW(left, top + 4 * lineHeight, _T("向下移动:S/鼠标操作"));
	pDC->TextOutW(left, top + 5 * lineHeight, _T("向左移动:A/鼠标操作"));
	pDC->TextOutW(left, top + 6 * lineHeight, _T("向右移动:D/鼠标操作"));
	pDC->TextOutW(left, top + 7 * lineHeight, _T("普通攻击：自动"));
	pDC->TextOutW(left, top + 8 * lineHeight, _T("武器1:1"));
	pDC->TextOutW(left, top + 9 * lineHeight, _T("武器2:2"));
	pDC->TextOutW(left, top + 10 * lineHeight, _T("武器3:3"));
	pDC->TextOutW(left, top + 11 * lineHeight, _T("终极武器：B"));
	pDC->TextOutW(left, top + 12 * lineHeight, _T("当前资源数："));
	CString str;
	str.Format(_T("当前得分：%d"), p1.getScore());
	pDC->TextOutW(left, top + 13 * lineHeight, str);
	str.Format(_T("生命值：%d"), p1.getLife());
	pDC->TextOutW(left, top + 14 * lineHeight, str);
	str.Format(_T("终极武器个数：%d"), p1.getBomb());
	pDC->TextOutW(left, top + 15 * lineHeight, str);
}

// CMFCPlaneGameView 绘制

void CMFCPlaneGameView::OnDraw(CDC* pDC)
{
	CMFCPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	switch (state) {
	case BEGIN: {
		readPlayerState(pDC);
		readBgPic(pDC);
		readBtnPic(pDC, &startBtn, IDB_GAME_START_BTN);
		readBtnPic(pDC, &overBtn, IDB_GAME_OVER_BTN);
		int lineHeight = 30;
		int left = GAME_WIDTH / 4;
		int top = GAME_HEIGHT / 8;
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(150, _T("微软雅黑"), pDC);
		pDC->SelectObject(&font);
		pDC->TextOutW(left, top, _T("游戏控制方式："));
		pDC->TextOutW(left, top + 1 * lineHeight,  _T("WSAD控制上下左右"));
		pDC->TextOutW(left, top + 2 * lineHeight,  _T("子弹自动发射，按B使用终极武器"));
		pDC->TextOutW(left, top + 4 * lineHeight,  _T("敌人说明:"));
		pDC->TextOutW(left, top + 5 * lineHeight,  _T("敌人会在屏幕上方随机出现，打中得一分"));
		pDC->TextOutW(left, top + 6 * lineHeight, _T("随着你得分越高，敌人会出现越来越快"));
		pDC->TextOutW(left, top + 7 * lineHeight, _T("当你得分达到100时，会出现BOSS"));
		pDC->TextOutW(left, top + 8 * lineHeight, _T("击败它吧，你会获得无上的荣耀！"));
		break;
	}
	case RUNNING: {
		/*双重缓冲处理*/
		CRect WndRect;
		GetClientRect(WndRect);
		int W = WndRect.Width();
		int H = WndRect.Height();
		CDC MemDC; //首先定义一个内存显示设备对象
		CBitmap MemBitmap;//定义一个位图对象
		MemDC.CreateCompatibleDC(pDC); //创建兼容设备dc
		MemBitmap.CreateCompatibleBitmap(pDC, W, H);
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0, 0, W, H, RGB(255, 255, 255));//填充初始颜色
		updateMap(&MemDC);
		pDC->BitBlt(WndRect.left, WndRect.top, W, H, &MemDC, 0, 0, SRCCOPY); //绘图到真实显示设备
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		break; 
	}
	case GOODEND: {
		readPlayerState(pDC);
		readBgPic(pDC);
		readBtnPic(pDC, &restartBtn, IDB_GAME_RESTART_BTN);
		readBtnPic(pDC, &overBtn, IDB_GAME_OVER_BTN);
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(150, _T("微软雅黑"), pDC);
		pDC->SelectObject(&font);
		int lineHeight = 30;
		int left = GAME_WIDTH / 4;
		int top = GAME_HEIGHT / 3;
		pDC->TextOutW(left, top, _T("祝贺你！通关了本游戏"));
		pDC->TextOutW(left, top + lineHeight, _T("你维护了地球的和平，人类永不忘记！！！"));
		CString str;
		str.Format(_T("你的最终得分:%d"), p1.getScore());
		pDC->TextOutW(left, top + 2 * lineHeight, str);
		break;
	}
	case BADEND: {
		readPlayerState(pDC);
		readBgPic(pDC);
		readBtnPic(pDC, &restartBtn, IDB_GAME_RESTART_BTN);
		readBtnPic(pDC, &overBtn, IDB_GAME_OVER_BTN);
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(150, _T("微软雅黑"), pDC);
		pDC->SelectObject(&font);
		int lineHeight = 30;
		int left = GAME_WIDTH / 4;
		int top = GAME_HEIGHT / 3;
		pDC->TextOutW(left, top, _T("很遗憾，你的战机被击毁了。。。"));
		pDC->TextOutW(left, top + lineHeight, _T("你的敌人现在正在很高兴地举行庆功party"));
		CString str;
		str.Format(_T("你的最终得分:%d"),p1.getScore());
		pDC->TextOutW(left, top + 2*lineHeight, str);
		break; 
	}
	}
}


// CMFCPlaneGameView 打印

BOOL CMFCPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCPlaneGameView 诊断

#ifdef _DEBUG
void CMFCPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPlaneGameDoc* CMFCPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPlaneGameDoc)));
	return (CMFCPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPlaneGameView 消息处理程序


int CMFCPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	state = BEGIN;
	int x = PLAY_WIDTH/3;
	int y = PLAY_HEIGHT/3*2;
	startBtn.SetRect(x, y, x + 300, y + 41);
	restartBtn.SetRect(x, y, x + 300, y + 41);
	y += 100;
	overBtn.SetRect(x, y, x + 300, y + 41);
	p1.setInitPlayer(0,0,0,0);
	return 0;
}

void CMFCPlaneGameView::addEnermy()
{
	cnt++;
	if (cnt >= EnermyOccurSpeed) {
		cnt = 0;
		enermyArray.push_back(shared_ptr<Enermy>(new OrdinaryEnermy(
			1,
			rand() % PLAY_WIDTH - 3,
			rand() % 10 + 1,
			200)));
	}
	/*敌机发射子弹*/
	for (list<shared_ptr<Enermy> >::iterator it = enermyArray.begin(); it != enermyArray.end(); it++) {
		OrdinaryEnermy* oe = dynamic_cast<OrdinaryEnermy*>(&*(*it));
		if (oe != nullptr) {
			oe->shoot(enermyArray);
			continue;
		}
	}
}

void CMFCPlaneGameView::bossComing()
{
	enermyArray.clear();
	BOSS = true;
	enermyArray.push_back(shared_ptr<Enermy>(new BossEnermy(1, PLAY_WIDTH / 2, 5)));
}

void CMFCPlaneGameView::bossDo()
{
	for (list<shared_ptr<Enermy> >::iterator it = enermyArray.begin(); it != enermyArray.end(); it++) {
		BossEnermy * be = dynamic_cast<BossEnermy*>(&*(*it));
		if (be != nullptr) {
			be->shoot(enermyArray);
			continue;
		}

	}
}

void CMFCPlaneGameView::updateLogic()
{
	EnermyOccurSpeed = 50 - p1.getScore()/5;
	if (EnermyOccurSpeed < 30)
		EnermyOccurSpeed = 30;
	p1.addBullet();
	/*增加敌人*/
	if (p1.getScore() < 100)
		addEnermy();
	else if (!BOSS) {
		bossComing();
		return;
	}
	else if (BOSS) {
		bossDo();
	}
	for (list<shared_ptr<Enermy> >::iterator it = enermyArray.begin(); it != enermyArray.end();) {
		if (p1.checkHit((*it)->getX(), (*it)->getY(),(*it)->getPicHeight(),(*it)->getPicWidth())) {
			it = enermyArray.erase(it);
			p1.getDamaged();
			if (p1.getLife() == 0)
				badEnd();
		}
		else if ((*it)->checkBorder(1, 2, PLAY_HEIGHT - 3, PLAY_WIDTH - 3))
			it++;
		else
			it = enermyArray.erase(it);
	}
	p1.updateBullet(enermyArray);
	for_each(enermyArray.begin(), enermyArray.end(), [](shared_ptr<Enermy> pe)->void {
		pe->move();
	});
	if (p1.getScore() >= 1000)
		goodEnd();
}

void CMFCPlaneGameView::updateMap(CDC *pDC)
{
	readPlayerState(pDC);
	roll = (roll - 1 + PLAY_HEIGHT)%PLAY_HEIGHT;
	CPngImage image;
	CBitmap bitmap;
	image.Load(IDB_BG, AfxGetInstanceHandle());
	bitmap.Attach(image.Detach());
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC); 
	dcCompatible.SelectObject(&bitmap);
	pDC->AlphaBlend(0,
		0,
		PLAY_WIDTH,
		PLAY_HEIGHT - roll,
		&dcCompatible,
		0,
		(double)roll / PLAY_HEIGHT * 480,
		852,
		480-(double)roll/PLAY_HEIGHT*480,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
	pDC->AlphaBlend(0,
		PLAY_HEIGHT-roll - 1,
		PLAY_WIDTH,
		roll,
		&dcCompatible,
		0,
		1,
		852,
		(double)roll / PLAY_HEIGHT * 480,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });

	p1.updateMap(pDC);
	for_each(enermyArray.begin(), enermyArray.end(), [&](shared_ptr<Enermy> pe)->void {
		pe->updateMap(pDC);
	});
	p1.bulletUpdateMap(pDC);
}

void CMFCPlaneGameView::goodEnd()
{
	KillTimer(ID_GAME_TIMER);
	CGoodEndDlg dlg;
	dlg.DoModal();
	state = GOODEND;
}

void CMFCPlaneGameView::badEnd()
{
	KillTimer(ID_GAME_TIMER);
	CBadEndDlg dlg;
	dlg.DoModal();
	state = BADEND;
}

void CMFCPlaneGameView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mouseControl) {
		p1.setPosition(point.y, point.x);
		p1.checkBorder(1, 2, PLAY_HEIGHT - 3, PLAY_WIDTH - 3);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nChar) {
	case '1':p1.control('1'); break;
	case '2':p1.control('2'); break;
	case '3':p1.control('3'); break;
	case 'B':p1.control('b'); break;
	case 'P':KillTimer(ID_GAME_TIMER);break;
	case 'C':SetTimer(ID_GAME_TIMER, 10, NULL); break;
	}
	if (kbControl) {
		switch (nChar) {
		case 'W':p1.control('w'); break;
		case 'S':p1.control('s'); break;
		case 'A':p1.control('a'); break;
		case 'D':p1.control('d'); break;
		}
	}
	p1.checkBorder(1, 2, PLAY_HEIGHT - 3, PLAY_WIDTH - 3);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	updateLogic();
	Invalidate();
	UpdateWindow();
	CView::OnTimer(nIDEvent);
}


BOOL CMFCPlaneGameView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*防止闪烁，返回TRUE，采用双重缓冲*/
	return true;
}

void CMFCPlaneGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (state) {
	case BEGIN: {
		if (startBtn.PtInRect(point)) {
			state = RUNNING;
			/*游戏初始化*/
			SetTimer(ID_GAME_TIMER, 10, NULL); //100 FPS
			p1.setInitPlayer(PLAY_HEIGHT - 3 - p1.picHeight / 2, PLAY_WIDTH / 2, 3, 3);
			cnt = 0;
			EnermyOccurSpeed = 30;
			roll = 0;
			mouseControl = true;
			kbControl = true;
		}
		else if (overBtn.PtInRect(point)) {
			exit(0);
		}
		break; 
	}
	case RUNNING:break;
	case GOODEND: {
		if (restartBtn.PtInRect(point)) {
			state = BEGIN;
		}
		else if (overBtn.PtInRect(point)) {
			exit(0);
		}
		break;
	}
	case BADEND: {
		if (restartBtn.PtInRect(point)) {
			state = BEGIN;
		}
		else if (overBtn.PtInRect(point)) {
			exit(0);
		}
		break;
	}
	}
	Invalidate();
	UpdateWindow();
	CView::OnLButtonDown(nFlags, point);
}
