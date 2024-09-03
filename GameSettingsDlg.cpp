// GameSettings.cpp : implementation file
//
#include "pch.h"
#include "afxdialogex.h"
#include "GameSettingsDlg.h"


// GameSettings dialog

IMPLEMENT_DYNAMIC(GameSettings, CDialogEx)

GameSettings::GameSettings(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

GameSettings::~GameSettings()
{
}

void GameSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, PlayerCountSlider);
	PlayerCountSlider.SetRangeMin(2);
	PlayerCountSlider.SetRangeMax(10);
	DDX_Control(pDX, IDC_EDIT1, PlayerCountEdit);

	DDX_Control(pDX, IDC_CHECK1, FullscreenCheck);
}


BEGIN_MESSAGE_MAP(GameSettings, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &GameSettings::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, &GameSettings::OnEnChangeEdit1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GameSettings::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// GameSettings message handlers


void GameSettings::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}





void GameSettings::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void GameSettings::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	// 
	//PlayerCountEdit.SetWindowTextW(PlayerCountSlider.GetPos())
	PlayerCountEdit.SetWindowText(std::to_string(PlayerCountSlider.GetPos()).c_str());
	*pResult = 0;
}
