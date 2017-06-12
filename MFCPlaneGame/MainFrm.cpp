
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MFCPlaneGame.h"
#include"MFCPlaneGameDoc.h"
#include"MFCPlaneGameView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL, &CMainFrame::OnUpdateMousecontrol)
	ON_COMMAND(ID_MOUSECONTROL, &CMainFrame::OnMousecontrol)
	ON_COMMAND(ID_KBCONTROL, &CMainFrame::OnKbcontrol)
	ON_UPDATE_COMMAND_UI(ID_KBCONTROL, &CMainFrame::OnUpdateKbcontrol)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}*/

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnUpdateMousecontrol(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CMFCPlaneGameView* p = (CMFCPlaneGameView*)GetActiveView();
	pCmdUI->SetCheck(p->getMouseControl());
}


void CMainFrame::OnMousecontrol()
{
	// TODO: �ڴ���������������
	CMFCPlaneGameView* p = (CMFCPlaneGameView*)GetActiveView();
	p->setMouseControl(!p->getMouseControl());
}


void CMainFrame::OnKbcontrol()
{
	// TODO: �ڴ���������������
	CMFCPlaneGameView* p = (CMFCPlaneGameView*)GetActiveView();
	p->setKbControl(!p->getKbControl());
}


void CMainFrame::OnUpdateKbcontrol(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	CMFCPlaneGameView* p = (CMFCPlaneGameView*)GetActiveView();
	pCmdUI->SetCheck(p->getKbControl());
}
