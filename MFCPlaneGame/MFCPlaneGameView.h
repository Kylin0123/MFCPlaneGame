
// MFCPlaneGameView.h : CMFCPlaneGameView 类的接口
//

#pragma once

#include"Player.h"
#include<list>
#include<memory>
using namespace std;

typedef enum {BEGIN,RUNNING,GOODEND,BADEND} STATE;

class CMFCPlaneGameView : public CView
{
protected: // 仅从序列化创建
	CMFCPlaneGameView();
	DECLARE_DYNCREATE(CMFCPlaneGameView)

// 特性
public:
	CMFCPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFCPlaneGameView.cpp 中的调试版本
inline CMFCPlaneGameDoc* CMFCPlaneGameView::GetDocument() const
   { return reinterpret_cast<CMFCPlaneGameDoc*>(m_pDocument); }
#endif

