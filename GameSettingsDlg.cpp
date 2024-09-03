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

	DDX_Control(pDX, IDC_COMBO1, VictoryConditionSelect);
	VictoryConditionSelect.AddString("None");
	VictoryConditionSelect.AddString("Match wins");
	VictoryConditionSelect.AddString("Points");
	VictoryConditionSelect.SelectString(0, "None");

	DDX_Control(pDX, IDC_EDIT2, VictoryConditionEdit);

	DDX_Control(pDX, IDC_STATIC3, VictoryConditionText);
}


BEGIN_MESSAGE_MAP(GameSettings, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &GameSettings::OnLbnSelchangeList1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GameSettings::OnNMCustomdrawSlider1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &GameSettings::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &GameSettings::OnEnChangeEdit2)
END_MESSAGE_MAP()


// GameSettings message handlers


void GameSettings::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}




void GameSettings::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	PlayerCountEdit.SetWindowText(std::to_string(PlayerCountSlider.GetPos()).c_str());
	*pResult = 0;
}


void GameSettings::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	switch (VictoryConditionSelect.GetCurSel()) {
	case 0:
		VictoryConditionEdit.SetWindowTextA("");
		VictoryConditionEdit.ShowWindow(0);
		VictoryConditionText.ShowWindow(0);

		break;
	case 1:
		VictoryConditionEdit.SetWindowTextA("");
		VictoryConditionText.SetWindowTextA("Match wins needed for game victory (default: 5)");
		VictoryConditionEdit.ShowWindow(1);
		VictoryConditionText.ShowWindow(1);
		break;
	case 2:
		VictoryConditionEdit.SetWindowTextA("");
		VictoryConditionText.SetWindowTextA("Points needed for game victory (default: 500)");
		VictoryConditionEdit.ShowWindow(1);
		VictoryConditionText.ShowWindow(1);
		break;
	}
}


void GameSettings::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}




