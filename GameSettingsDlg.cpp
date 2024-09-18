// GameSettings.cpp : implementation file
//
#include "pch.h"
#include "afxdialogex.h"
#include "GameSettingsDlg.h"


// GameSettings dialog

IMPLEMENT_DYNAMIC(GameSettings, CDialogEx)


GameSettings::GameSettings(SavedGameSettings* gmSet, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	settings = gmSet;
}
//
//GameSettings::GameSettings(SavedGameSettings& gameSet)
//{
//	gmSet = gameSet;
//}

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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &GameSettings::OnNMCustomdrawSlider1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &GameSettings::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &GameSettings::OnBnClickedOk)
END_MESSAGE_MAP()


// GameSettings message handlers


void GameSettings::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	PlayerCountEdit.SetWindowText(std::to_string(PlayerCountSlider.GetPos()).c_str());
	*pResult = 0;
}


void GameSettings::OnCbnSelchangeCombo1()
{
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


void GameSettings::OnBnClickedOk()
{
	settings->playerCount = PlayerCountSlider.GetPos();
	if (FullscreenCheck.GetCheck()) {
		settings->isFullscreen = true;
	}
	int gameCondition = GetDlgItemInt(IDC_EDIT2);
	switch (VictoryConditionSelect.GetCurSel()) {
	case 0:
		settings->GameType = 0;
		break;
	case 1:
		settings->GameType = 1;
		if (gameCondition != 0) settings->winsNeeded = gameCondition;
		break;
	case 2:
		settings->GameType = 2;
		if (gameCondition != 0) settings->pointsNeeded = gameCondition;
		break;
	}

	CDialogEx::OnOK();
}
