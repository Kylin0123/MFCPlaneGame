#pragma once


// CGoodEndDlg �Ի���

class CGoodEndDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGoodEndDlg)

public:
	CGoodEndDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGoodEndDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GOODEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
