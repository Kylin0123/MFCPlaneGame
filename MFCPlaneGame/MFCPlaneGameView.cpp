
// MFCPlaneGameView.cpp : CMFCPlaneGameView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMFCPlaneGameView ����/����

CMFCPlaneGameView::CMFCPlaneGameView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCPlaneGameView::~CMFCPlaneGameView()
{
}

BOOL CMFCPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// ��ȡ����ͼƬ
void CMFCPlaneGameView::readBgPic(CDC* pDC)
{
	CPngImage image;
	CBitmap bitmap;
	image.Load(IDB_BG, AfxGetInstanceHandle());
	bitmap.Attach(image.Detach());
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);  // �����뵱ǰDC��pDC�����ݵ�DC
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
	dcCompatible.CreateCompatibleDC(pDC);  // �����뵱ǰDC��pDC�����ݵ�DC
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
	font.CreatePointFont(150, _T("΢���ź�"), pDC);
	pDC->SelectObject(&font);
	int lineHeight = 30;
	int left = PLAY_WIDTH;
	int top = PLAY_HEIGHT/10;
	pDC->TextOutW(left, top + lineHeight, _T("����˵����"));
	pDC->TextOutW(left, top + 1 * lineHeight, _T("��ͣ��Ϸ:P"));
	pDC->TextOutW(left, top + 2 * lineHeight, _T("������Ϸ��C"));
	pDC->TextOutW(left, top + 3 * lineHeight, _T("�����ƶ�:W/������"));
	pDC->TextOutW(left, top + 4 * lineHeight, _T("�����ƶ�:S/������"));
	pDC->TextOutW(left, top + 5 * lineHeight, _T("�����ƶ�:A/������"));
	pDC->TextOutW(left, top + 6 * lineHeight, _T("�����ƶ�:D/������"));
	pDC->TextOutW(left, top + 7 * lineHeight, _T("��ͨ�������Զ�"));
	pDC->TextOutW(left, top + 8 * lineHeight, _T("����1:1"));
	pDC->TextOutW(left, top + 9 * lineHeight, _T("����2:2"));
	pDC->TextOutW(left, top + 10 * lineHeight, _T("����3:3"));
	pDC->TextOutW(left, top + 11 * lineHeight, _T("�ռ�������B"));
	pDC->TextOutW(left, top + 12 * lineHeight, _T("��ǰ��Դ����"));
	CString str;
	str.Format(_T("��ǰ�÷֣�%d"), p1.getScore());
	pDC->TextOutW(left, top + 13 * lineHeight, str);
	str.Format(_T("����ֵ��%d"), p1.getLife());
	pDC->TextOutW(left, top + 14 * lineHeight, str);
	str.Format(_T("�ռ�����������%d"), p1.getBomb());
	pDC->TextOutW(left, top + 15 * lineHeight, str);
}

// CMFCPlaneGameView ����

void CMFCPlaneGameView::OnDraw(CDC* pDC)
{
	CMFCPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
		font.CreatePointFont(150, _T("΢���ź�"), pDC);
		pDC->SelectObject(&font);
		pDC->TextOutW(left, top, _T("��Ϸ���Ʒ�ʽ��"));
		pDC->TextOutW(left, top + 1 * lineHeight,  _T("WSAD������������"));
		pDC->TextOutW(left, top + 2 * lineHeight,  _T("�ӵ��Զ����䣬��Bʹ���ռ�����"));
		pDC->TextOutW(left, top + 4 * lineHeight,  _T("����˵��:"));
		pDC->TextOutW(left, top + 5 * lineHeight,  _T("���˻�����Ļ�Ϸ�������֣����е�һ��"));
		pDC->TextOutW(left, top + 6 * lineHeight, _T("������÷�Խ�ߣ����˻����Խ��Խ��"));
		pDC->TextOutW(left, top + 7 * lineHeight, _T("����÷ִﵽ100ʱ�������BOSS"));
		pDC->TextOutW(left, top + 8 * lineHeight, _T("�������ɣ���������ϵ���ҫ��"));
		break;
	}
	case RUNNING: {
		/*˫�ػ��崦��*/
		CRect WndRect;
		GetClientRect(WndRect);
		int W = WndRect.Width();
		int H = WndRect.Height();
		CDC MemDC; //���ȶ���һ���ڴ���ʾ�豸����
		CBitmap MemBitmap;//����һ��λͼ����
		MemDC.CreateCompatibleDC(pDC); //���������豸dc
		MemBitmap.CreateCompatibleBitmap(pDC, W, H);
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0, 0, W, H, RGB(255, 255, 255));//����ʼ��ɫ
		updateMap(&MemDC);
		pDC->BitBlt(WndRect.left, WndRect.top, W, H, &MemDC, 0, 0, SRCCOPY); //��ͼ����ʵ��ʾ�豸
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
		font.CreatePointFont(150, _T("΢���ź�"), pDC);
		pDC->SelectObject(&font);
		int lineHeight = 30;
		int left = GAME_WIDTH / 4;
		int top = GAME_HEIGHT / 3;
		pDC->TextOutW(left, top, _T("ף���㣡ͨ���˱���Ϸ"));
		pDC->TextOutW(left, top + lineHeight, _T("��ά���˵���ĺ�ƽ�������������ǣ�����"));
		CString str;
		str.Format(_T("������յ÷�:%d"), p1.getScore());
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
		font.CreatePointFont(150, _T("΢���ź�"), pDC);
		pDC->SelectObject(&font);
		int lineHeight = 30;
		int left = GAME_WIDTH / 4;
		int top = GAME_HEIGHT / 3;
		pDC->TextOutW(left, top, _T("���ź������ս���������ˡ�����"));
		pDC->TextOutW(left, top + lineHeight, _T("��ĵ����������ںܸ��˵ؾ����칦party"));
		CString str;
		str.Format(_T("������յ÷�:%d"),p1.getScore());
		pDC->TextOutW(left, top + 2*lineHeight, str);
		break; 
	}
	}
}


// CMFCPlaneGameView ��ӡ

BOOL CMFCPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCPlaneGameView ���

#ifdef _DEBUG
void CMFCPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPlaneGameDoc* CMFCPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPlaneGameDoc)));
	return (CMFCPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPlaneGameView ��Ϣ�������


int CMFCPlaneGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	/*�л������ӵ�*/
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
	/*���ӵ���*/
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (mouseControl) {
		p1.setPosition(point.y, point.x);
		p1.checkBorder(1, 2, PLAY_HEIGHT - 3, PLAY_WIDTH - 3);
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*��ֹ��˸������TRUE������˫�ػ���*/
	return true;
}

void CMFCPlaneGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (state) {
	case BEGIN: {
		if (startBtn.PtInRect(point)) {
			state = RUNNING;
			/*��Ϸ��ʼ��*/
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
