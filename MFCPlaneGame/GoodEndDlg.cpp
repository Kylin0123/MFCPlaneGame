// GoodEndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCPlaneGame.h"
#include "GoodEndDlg.h"
#include "afxdialogex.h"


// CGoodEndDlg �Ի���

IMPLEMENT_DYNAMIC(CGoodEndDlg, CDialogEx)

CGoodEndDlg::CGoodEndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GOODEND, pParent)
{

}

CGoodEndDlg::~CGoodEndDlg()
{
}

void CGoodEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGoodEndDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGoodEndDlg ��Ϣ�������


HBRUSH CGoodEndDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	CFont font;
	font.CreatePointFont(150, _T("΢���ź�"));
	pDC->SelectObject(&font);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
