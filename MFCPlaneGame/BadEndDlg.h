#pragma once


// CBadEndDlg 对话框

class CBadEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBadEndDlg)

public:
	CBadEndDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBadEndDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BADEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
