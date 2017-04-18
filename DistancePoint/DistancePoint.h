
// DistancePoint.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


#define WM_USER_PERSENT (WM_USER+1)  
// CDistancePointApp:
// О реализации данного класса см. DistancePoint.cpp
//

class CDistancePointApp : public CWinApp
{
public:
	CDistancePointApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDistancePointApp theApp;