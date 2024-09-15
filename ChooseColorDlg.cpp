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
	ON_BN_CLICKED(IDC_RED, &ChooseColorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_YELLOW, &ChooseColorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_GREEN, &ChooseColorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BLUE, &ChooseColorDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// ChooseColorDlg message handlers


void ChooseColorDlg::OnBnClickedButton1()
{
	chosenColor = IDC_RED;
	this->EndDialog(IDOK);
}


void ChooseColorDlg::OnBnClickedButton2()
{
	chosenColor = IDC_YELLOW;
	this->EndDialog(IDOK);
}


void ChooseColorDlg::OnBnClickedButton3()
{
	chosenColor = IDC_GREEN;
	this->EndDialog(IDOK);
}


void ChooseColorDlg::OnBnClickedButton4()
{
	chosenColor = IDC_BLUE;
	this->EndDialog(IDOK);
}
