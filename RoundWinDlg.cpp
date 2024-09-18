// RoundWinDlg.cpp : implementation file
//

#include "pch.h"
#include "Uno.h"
#include "afxdialogex.h"
#include "RoundWinDlg.h"


// RoundWinDlg dialog

IMPLEMENT_DYNAMIC(RoundWinDlg, CDialogEx)

RoundWinDlg::RoundWinDlg(int playerID, bool roundWin, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	getWinner(playerID, roundWin);
	

}

RoundWinDlg::~RoundWinDlg()
{
}

void RoundWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC2, winText);
}

BOOL RoundWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LPCTSTR szTemp = (LPCTSTR)str;
	winText.SetWindowTextA(szTemp);
	return TRUE;
}

void RoundWinDlg::getWinner(int playerID, bool roundWin)
{
	
	if (playerID == 0) {
		if (roundWin) {
			str.Format("You have won this round! Continue?");
		}
		else {
			str.Format("You have won the game! Continue?");
		}
	}
	else {
		if (roundWin) {
			str.Format("Opponent %u has won this round! Continue?",playerID);
		}
		else {
			str.Format("Opponent %u has won the game! Continue?",playerID);
		}
	}
	//winText.SetWindowTextA(szTemp);
}


BEGIN_MESSAGE_MAP(RoundWinDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RoundWinDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RoundWinDlg message handlers


void RoundWinDlg::OnBnClickedOk()
{
	this->EndDialog(IDOK);
	CDialogEx::OnOK();
}
