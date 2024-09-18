#pragma once
#include "afxdialogex.h"


// RoundWinDlg dialog

class RoundWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RoundWinDlg)

public:
	RoundWinDlg(int playerID, bool roundWin, CWnd* pParent = nullptr);   // standard constructor
	virtual ~RoundWinDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString str;
	CStatic winText;
	BOOL OnInitDialog();
public:
	void getWinner(int playerID, bool roundWin);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

};
