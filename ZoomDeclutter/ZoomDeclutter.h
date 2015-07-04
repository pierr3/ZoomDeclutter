// ZoomDeclutter.h : main header file for the ZoomDeclutter DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "ZoomDeclutterPlugin.h"

// CZoomDeclutterApp
// See ZoomDeclutter.cpp for the implementation of this class
//

class CZoomDeclutterApp : public CWinApp
{
public:
	CZoomDeclutterApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
