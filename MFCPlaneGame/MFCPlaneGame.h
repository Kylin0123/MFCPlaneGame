
// MFCPlaneGame.h : MFCPlaneGame Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCPlaneGameApp:
// �йش����ʵ�֣������ MFCPlaneGame.cpp
//

class CMFCPlaneGameApp : public CWinApp
{
public:
	CMFCPlaneGameApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCPlaneGameApp theApp;
