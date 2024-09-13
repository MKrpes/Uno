#pragma once
#include "afxdialogex.h"


// ChooseColorDlg dialog

class ChooseColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseColorDlg)

public:
	ChooseColorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ChooseColorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
