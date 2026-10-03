
// UnoGame.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Uno.h"
#include "MainFrm.h"
#include"GameSettingsDlg.h"
#include"View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnoGameApp

BEGIN_MESSAGE_MAP(CUnoGameApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CUnoGameApp::OnAppAbout)
END_MESSAGE_MAP()


// CUnoGameApp construction

CUnoGameApp::CUnoGameApp() noexcept
{
	SetAppID(_T("UnoGame.AppID.NoVersion"));
}

// The one and only CUnoGameApp object

CUnoGameApp theApp;


// CUnoGameApp initialization

BOOL CUnoGameApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object

	// create and load the frame with its resources



	GameSettings gameSettingsDlg(&gameSet,nullptr);
	if(gameSettingsDlg.DoModal() == IDOK) {
		game = std::make_unique<Game>(gameSet);
		CMainFrame* pFrame = new CMainFrame(*game);
		if (!pFrame)
			return FALSE;
		m_pMainWnd=pFrame;
		pFrame->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
			nullptr);
		if (gameSet.isFullscreen) {
			pFrame->ModifyStyle(WS_OVERLAPPEDWINDOW, 0);
			pFrame->ModifyStyle(WS_EX_CLIENTEDGE, 0);
			pFrame->ShowWindow(SW_SHOWMAXIMIZED);
		}
		else {
			pFrame->ShowWindow(SW_SHOW);
		}
		pFrame->UpdateWindow();
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int CUnoGameApp::ExitInstance()
{
	GdiplusShutdown(m_gdiplusToken);
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CUnoGameApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CUnoGameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CUnoGameApp message handlers




