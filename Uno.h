
// UnoGame.h : main header file for the UnoGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include"SavedGameSettings.h"
#include <gdiplus.h>
#include"Game.h"
using namespace Gdiplus;




// CUnoGameApp:
// See UnoGame.cpp for the implementation of this class
//

class CUnoGameApp : public CWinApp
{
public:
	CUnoGameApp() noexcept;
	ULONG_PTR m_gdiplusToken;
	SavedGameSettings gameSet;
	//Game game;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUnoGameApp theApp;
