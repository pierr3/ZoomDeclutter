// ZoomDeclutter.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ZoomDeclutter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CZoomDeclutterApp

BEGIN_MESSAGE_MAP(CZoomDeclutterApp, CWinApp)
END_MESSAGE_MAP()

// CZoomDeclutterApp construction

CZoomDeclutterApp::CZoomDeclutterApp()
{
	
}

// The one and only CZoomDeclutterApp object

CZoomDeclutterApp theApp;

// CZoomDeclutterApp initialization

BOOL CZoomDeclutterApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CZoomDeclutterPlugin *pMyPlugIn = NULL;

void __declspec (dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn ** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// allocate
	*ppPlugInInstance = pMyPlugIn = new CZoomDeclutterPlugin();
}

void __declspec (dllexport) EuroScopePlugInExit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	delete pMyPlugIn;
}
