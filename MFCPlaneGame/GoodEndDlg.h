#pragma once


// CGoodEndDlg 对话框

class CGoodEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGoodEndDlg)

public:
	CGoodEndDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGoodEndDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GOODEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
