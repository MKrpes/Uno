
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

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("UnoGame.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CUnoGameApp object

CUnoGameApp theApp;


// CUnoGameApp initialization

BOOL CUnoGameApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
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

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object

	// create and load the frame with its resources



	GameSettings gameSettingsDlg(&gameSet,nullptr);
	if(gameSettingsDlg.DoModal() == IDOK) {
		Game* game=new Game(gameSet);
		//CFrameWnd* pFrame = new CMainFrame;
		CMainFrame* pFrame = new CMainFrame;
		if (!pFrame)
			return FALSE;
		m_pMainWnd = pFrame;
		pFrame->m_wndView.loadGame(game);
		pFrame->LoadFrame(IDR_MAINFRAME,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
			nullptr);
		if (gameSet.isFullscreen) {
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
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);
	GdiplusShutdown(m_gdiplusToken);

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




