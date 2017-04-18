
// DistancePointDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "DistancePoint.h"
#include "DistancePointDlg.h"
#include "afxdialogex.h"
//#include "memory"
//using namespace std;
#include "boost\shared_ptr.hpp"
#include "boost\make_shared.hpp"
using namespace boost;
//using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CDistancePointDlg



CDistancePointDlg::CDistancePointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDistancePointDlg::IDD, pParent)
	, m_strEditPathLine(_T(""))
	, m_strEditDistance(_T(""))
	, m_strEditPathPointRez(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDistancePointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITPATHLINE, m_cEditPathLine);
	DDX_Text(pDX, IDC_EDITPATHLINE, m_strEditPathLine);
//	DDX_Control(pDX, IDC_EDITPATHLINE2, m_cEditPathPoint);
	DDX_Text(pDX, IDC_EDITPATHLINE2, m_strEditDistance);
	DDX_Control(pDX, IDC_STATICRUN, m_cStaticRun);
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress);
	DDX_Control(pDX, IDC_EDITPATHLINE3, m_cEditPathPointRez);
	DDX_Text(pDX, IDC_EDITPATHLINE3, m_strEditPathPointRez);
}

BEGIN_MESSAGE_MAP(CDistancePointDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONPATHLINE, &CDistancePointDlg::OnBnClickedButtonpathline)
//	ON_BN_CLICKED(IDC_BUTTONPATHPOINT, &CDistancePointDlg::OnBnClickedButtonpathpoint)
	ON_BN_CLICKED(IDC_BUTTONPATHPOINT2, &CDistancePointDlg::OnBnClickedButtonpathpoint2)
	ON_BN_CLICKED(IDRUN, &CDistancePointDlg::OnBnClickedRun)
	ON_MESSAGE(WM_USER_PERSENT, CountPercent)
END_MESSAGE_MAP()


// обработчики сообщений CDistancePointDlg

BOOL CDistancePointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	m_cProgress.SetRange32(0, 100);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDistancePointDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDistancePointDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDistancePointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CDistancePointDlg::CountPercent(WPARAM wParam, LPARAM lParam)
{
	CString* str = (CString*)lParam;
	m_cStaticRun.SetWindowText(*str);
	m_cProgress.SetPos((int)wParam);

	return(0);
}
void CDistancePointDlg::OnBnClickedButtonpathline()
{
	
	//Создаем стандартный блок диалога "Открытия файла"
	CString str;

	shared_ptr<CFileDialog> fDlg(new CFileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		_T("ASCII  (*.dat)|*.dat||")));
		_T("Any file |*.*||")));

	fDlg->m_ofn.lpstrFile = str.GetBuffer(10000);
	fDlg->m_ofn.nMaxFile = 10000;


	if (fDlg->DoModal() == IDOK)
	{
		m_strEditPathLine = fDlg->GetPathName();
		m_cEditPathLine.SetWindowTextW(fDlg->GetPathName());
		m_strEditPathPointRez = fDlg->GetPathName();
		CString extension = fDlg->GetFileExt();
		m_strEditPathPointRez.Replace(extension, L"result." + extension);
		m_cEditPathPointRez.SetWindowTextW(m_strEditPathPointRez);
	}
}

//void CDistancePointDlg::OnBnClickedButtonpathpoint() {}

void CDistancePointDlg::OnBnClickedButtonpathpoint2()
{
	//Создаем стандартный блок диалога "Открытия файла"
	CString str;

	shared_ptr<CFileDialog> fDlg(new CFileDialog(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		_T("ASCII  (*.dat)|*.dat||")));
		_T("Any file |*.*||")));

	fDlg->m_ofn.lpstrFile = str.GetBuffer(10000);
	fDlg->m_ofn.nMaxFile = 10000;


	if (fDlg->DoModal() == IDOK)
	{
		m_strEditPathPointRez = fDlg->GetPathName();
		m_cEditPathPointRez.SetWindowTextW(fDlg->GetPathName());
	}

}


void CDistancePointDlg::OnBnClickedRun()
{
	UpdateData();

	double R = _ttof(m_strEditDistance);
	if (R <= 0 || R > 100)
	{
		MessageBox(L"Дистанция не задана или задана некорректно");
		return;
	}

	CString str;
	auto pFInDat = make_shared<CStdioFile>(m_strEditPathLine, CFile::modeRead);
	if (pFInDat.use_count() == 0)
	{
		MessageBox(L"Неверный путь к файлу с проложением профиля");
		return;
	}
	int CountPointLine = 0;

	str=(L"Определяем число строк в файле с координатами профиля");
	SendMessage(WM_USER_PERSENT, 0, (long)&str);
	while (pFInDat->ReadString(str))
	{
		if (str.FindOneOf(L"qwertyuiopasdfghjklzxcvbnmZXCVBNMASDFGHJKLQWERTYUIOP") >= 0)
		{
			continue;
		}
		CountPointLine++;
	}
	pFInDat->SeekToBegin();


	auto ptr_X = make_shared<double[]>(CountPointLine);
	auto ptr_Y = make_shared<double[]>(CountPointLine);
	auto ptr_Num = make_shared<int[]>(CountPointLine);



	for (int i = 0; i < CountPointLine; ++i)
	{
		pFInDat->ReadString(str);
		if (str.FindOneOf(L"qwertyuiopasdfghjklzxcvbnmZXCVBNMASDFGHJKLQWERTYUIOP") >= 0)
		{
			continue;
		}
		int pos = 0;
		ptr_X[i] = _ttof(str.Tokenize(L" \t,;", pos));
		ptr_Y[i] = _ttof(str.Tokenize(L" \t,;", pos));
		ptr_Num[i] = _ttoi(str.Tokenize(L" \t,;", pos));

		str.Format(_T("Считываем данные по профилю.Обработка строки %d Выполнено  %6.2f %1s"), i + 1, (i + 1) * 100.0l / CountPointLine, L"%");
		SendMessage(WM_USER_PERSENT, (WPARAM)((i + 1) * 100.0l / CountPointLine), (long)&str);
	}
	pFInDat->Close();

	pFInDat = make_shared<CStdioFile>(m_strEditPathPointRez, CFile::modeCreate | CFile::modeWrite);
	if (pFInDat.use_count() == 0)
	{
		MessageBox(L"Неверный путь к файлу результатов");
		return;
	}
	
	double XCross, YCross;
	int i = 0;
	double X0 = ptr_X[0];
	double Y0 = ptr_Y[0];
	str.Format(L"%15.4f\t%15.4f\t%15d%15.4f%15d%15d\n", X0, Y0);

	

	while (i + 1 < CountPointLine)
	{

		if (!CrossPointCurverToLine(X0, Y0, R, ptr_X[i], ptr_Y[i], ptr_X[i + 1], ptr_Y[i + 1], XCross, YCross, 2))
		{
			double xPart = (XCross - ptr_X[i]) * (XCross - ptr_X[i + 1]);
			double yPart = (YCross - ptr_Y[i]) * (YCross - ptr_Y[i + 1]);

			if ((xPart + yPart) <= 0.000001l)
			{
				str.Format(L"%15.4f\t%15.4f\n", X0, Y0);
				pFInDat->WriteString(str);

				X0 = XCross;
				Y0 = YCross;

				continue;
			}
			else
				i++;
		}
	}

	pFInDat->Close();
	MessageBox(L"Вычисления завершены");
}

///
///<summary> 
///
///
///</summary>
///
///
/// <param name="X0">X-coordinate of start point</param>
/// <param name="Y0">Y-coordinate of start point</param>
/// <param name="R">Distance next point will be from initial point at</param>
/// <param name="X1">X-coordinate of start-point of interval where intersection is to be found</param>
/// <param name="Y1">Y-coordinate of start-point of interval where intersection is to be found</param>
/// <param name="X2">X-coordinate of end-point of interval where intersection is to be found</param>
/// <param name="Y2">Y-coordinate of end-point of interval where intersection is to be found</param>
/// <param name="XCross">X-coordinate of intersection</param>
/// <param name="YCross">Y-coordinate of intersection</param>
/// <param name="NumPoint">
///		1, if cross point should be closer to start point (X1, Y1) of interval, 
///		and 2 (or anything but 1), if cross point should be near (X2, Y2) instead.
///	</param>
/// <returns>
///		-1 if cross point does not exist
///		0 if the assignment of whatever the point went successfully
///	</returns>
int CDistancePointDlg::CrossPointCurverToLine(double X0, double Y0, double R, double X1, double Y1, double X2, double Y2, 
		double &XCross, double &YCross, int NumPoint)
{

	int Count = 0;
	//Вычисляем коэффициенты квадратного уравнения
	double a, b, A, B, C;
	//Вычитаем из координат X0,Y0

	if (fabs(X2 - X1)>fabs(Y2 - Y1))
	{
		//Для повышения точности вычитаем из координат X0,Y0
		a = (Y2 - Y1) / (X2 - X1);
		b = ((Y1 - Y0) - a*(X1 - X0));
		A = 1.0l + a*a;
		B = 2.0l*(a*b);//B = 2.0l*(a*(b-Y0)-X0);
		C = b*b - R*R;//C = X0*X0+b*b-2.0l*b*Y0+Y0*Y0-R*R;
		//Решаем квадратное уравнение
		double D = B*B - 4.0l*A*C;
		if (D<0)
			return -1;

		double xp1 = X0 + (-B - sqrt(D)) / (2.0l*A);
		double yp1 = (xp1 - X1) / (X2 - X1)*(Y2 - Y1) + Y1;

		double xp2 = X0 + (-B + sqrt(D)) / (2.0l*A);
		double yp2 = (xp2 - X1) / (X2 - X1)*(Y2 - Y1) + Y1;

		if (NumPoint == 1)
		{
			double r1 = sqrt(pow(xp1 - X1, 2) + pow(yp1 - Y1, 2));
			double r2 = sqrt(pow(xp2 - X1, 2) + pow(yp2 - Y1, 2));
			if (r1<r2)
			{
				YCross = yp1;
				XCross = xp1;
			}
			else
			{
				YCross = yp2;
				XCross = xp2;
			}
		}
		else
		{
			double r1 = sqrt(pow(xp1 - X2, 2) + pow(yp1 - Y2, 2));
			double r2 = sqrt(pow(xp2 - X2, 2) + pow(yp2 - Y2, 2));
			if (r1<r2)
			{
				YCross = yp1;
				XCross = xp1;
			}
			else
			{
				YCross = yp2;
				XCross = xp2;
			}
		}
	}
	else
	{
		a = (X2 - X1) / (Y2 - Y1);
		b = ((X1 - X0) - a*(Y1 - Y0));
		A = 1.0l + a*a;
		B = 2.0l*(a*b);//B = 2.0l*(a*(b-X0)-Y0);
		C = b*b - R*R;//C = Y0*Y0+b*b-2.0l*b*X0+X0*X0-R*R;
		//Решаем квадратное уравнение
		double D = B*B - 4.0l*A*C;

		if (D<0)
			return -1;

		double yp1 = Y0 + (-B - sqrt(D)) / (2.0l*A);
		double xp1 = (yp1 - Y1) / (Y2 - Y1)*(X2 - X1) + X1;

		double yp2 = Y0 + (-B + sqrt(D)) / (2.0l*A);
		double xp2 = (yp2 - Y1) / (Y2 - Y1)*(X2 - X1) + X1;

		if (NumPoint == 1)
		{
			double r1 = sqrt(pow(xp1 - X1, 2) + pow(yp1 - Y1, 2));
			double r2 = sqrt(pow(xp2 - X1, 2) + pow(yp2 - Y1, 2));
			if (r1<r2)
			{
				YCross = yp1;
				XCross = xp1;
			}
			else
			{
				YCross = yp2;
				XCross = xp2;
			}
		}
		else
		{
			double r1 = sqrt(pow(xp1 - X2, 2) + pow(yp1 - Y2, 2));
			double r2 = sqrt(pow(xp2 - X2, 2) + pow(yp2 - Y2, 2));
			if (r1<r2)
			{
				YCross = yp1;
				XCross = xp1;

			}
			else
			{
				YCross = yp2;
				XCross = xp2;
			}
		}


		/*str.Format("a=%f,b=%f,D=%f,XCross=%f,YCross=%f,X0=%f,Y0=%f,X1=%f,Y1=%f,X2=%f,Y2=%f,R=%f,Count=%d\n",a,b,D,XCross,YCross,X0,Y0,X1,Y1,X2,Y2,R,Count);
		//MessageBox(str);
		pF = new CStdioFile("d:\\6000.dat",CFile::modeWrite);
		pF->SeekToEnd();
		pF->WriteString("\n");
		pF->WriteString(str);
		str.Format("xp1=%f,yp1=%f,xp2=%f,yp2=%f\n",xp1,yp1,xp2,yp2);
		pF->WriteString(str);
		pF->Close();
		*/
	}

	return Count;
}
