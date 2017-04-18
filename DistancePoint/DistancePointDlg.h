
// DistancePointDlg.h : файл заголовка
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CDistancePointDlg
class CDistancePointDlg : public CDialogEx
{
// Создание
public:
	CDistancePointDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_DISTANCEPOINT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT CountPercent(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonpathline();
	CEdit m_cEditPathLine;
	CString m_strEditPathLine;
	afx_msg void OnBnClickedButtonpathpoint();
//	CEdit m_cEditPathPoint;
	CString m_strEditDistance;
	CStatic m_cStaticRun;
	CProgressCtrl m_cProgress;
	afx_msg void OnBnClickedButtonpathpoint2();
	afx_msg void OnBnClickedRun();
	CEdit m_cEditPathPointRez;
	CString m_strEditPathPointRez;
	int CrossPointCurverToLine(double X0, double Y0, double R, double X1, double Y1, double X2, double Y2, double &XCross, double &YCross, int NumPoint);
};
