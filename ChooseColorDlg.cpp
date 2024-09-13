// ChooseColorDlg.cpp : implementation file
//

#include "pch.h"
#include "Uno.h"
#include "afxdialogex.h"
#include "ChooseColorDlg.h"


// ChooseColorDlg dialog

IMPLEMENT_DYNAMIC(ChooseColorDlg, CDialogEx)

ChooseColorDlg::ChooseColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

ChooseColorDlg::~ChooseColorDlg()
{
}

void ChooseColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChooseColorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChooseColorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChooseColorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ChooseColorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ChooseColorDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// ChooseColorDlg message handlers


void ChooseColorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}


void ChooseColorDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}


void ChooseColorDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}


void ChooseColorDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
}
