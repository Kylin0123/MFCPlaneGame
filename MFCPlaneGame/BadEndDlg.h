#pragma once


// CBadEndDlg �Ի���

class CBadEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBadEndDlg)

public:
	CBadEndDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBadEndDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BADEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
