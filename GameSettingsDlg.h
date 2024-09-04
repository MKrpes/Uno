#pragma once
#include "afxdialogex.h"
#include "Uno.h"
#include "SavedGameSettings.h"
#include<string>

// GameSettings dialog

class GameSettings : public CDialogEx
{
	DECLARE_DYNAMIC(GameSettings)

public:
	GameSettings(CWnd* pParent = nullptr);   // standard constructor
	virtual ~GameSettings();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl PlayerCountSlider;
	CEdit PlayerCountEdit;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	CButton FullscreenCheck;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox VictoryConditionSelect;
	CEdit VictoryConditionEdit;
	CStatic VictoryConditionText;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	SavedGameSettings settings;
};
