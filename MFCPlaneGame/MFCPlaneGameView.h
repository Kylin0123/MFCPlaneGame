
// MFCPlaneGameView.h : CMFCPlaneGameView ��Ľӿ�
//

#pragma once

#include"Player.h"
#include<list>
#include<memory>
using namespace std;

typedef enum {BEGIN,RUNNING,GOODEND,BADEND} STATE;

class CMFCPlaneGameView : public CView
{
protected: // �������л�����
	CMFCPlaneGameView();
	DECLARE_DYNCREATE(CMFCPlaneGameView)

// ����
public:
	CMFCPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool getMouseControl() { return mouseControl; }
	void setMouseControl(bool m) { mouseControl = m; }
	bool getKbControl() { return kbControl; }
	void setKbControl(bool k) { kbControl = k; }
private:
	STATE state;
	Player p1;
	list<shared_ptr<Enermy> > enermyArray;
	CRect startBtn;
	CRect overBtn;
	CRect restartBtn;
	bool mouseControl;
	bool kbControl;
	int cnt;
	int EnermyOccurSpeed;
	int roll;
	bool BOSS = false;
	void addEnermy();
	void bossComing();
	void bossDo();
	void updateLogic();
	void updateMap(CDC* pDC);
	void showMap() {};
	void goodEnd();
	void badEnd();
	void readBgPic(CDC* pDC);
	void readBtnPic(CDC* pDC, CRect *crect, UINT ID);
	void readPlayerState(CDC* pDC);
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFCPlaneGameView.cpp �еĵ��԰汾
inline CMFCPlaneGameDoc* CMFCPlaneGameView::GetDocument() const
   { return reinterpret_cast<CMFCPlaneGameDoc*>(m_pDocument); }
#endif

