// BadEndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCPlaneGame.h"
#include "BadEndDlg.h"
#include "afxdialogex.h"


// CBadEndDlg �Ի���

IMPLEMENT_DYNAMIC(CBadEndDlg, CDialogEx)

CBadEndDlg::CBadEndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CBadEndDlg::~CBadEndDlg()
{
}

void CBadEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBadEndDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CBadEndDlg ��Ϣ�������


HBRUSH CBadEndDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	CFont font;
	font.CreatePointFont(150, _T("΢���ź�"));
	pDC->SelectObject(&font);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
