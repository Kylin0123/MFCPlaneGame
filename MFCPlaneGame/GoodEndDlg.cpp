// GoodEndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCPlaneGame.h"
#include "GoodEndDlg.h"
#include "afxdialogex.h"


// CGoodEndDlg 对话框

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


// CGoodEndDlg 消息处理程序


HBRUSH CGoodEndDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	CFont font;
	font.CreatePointFont(150, _T("微软雅黑"));
	pDC->SelectObject(&font);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
