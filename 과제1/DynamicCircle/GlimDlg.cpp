
// GlimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Glim.h"
#include "GlimDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimDlg dialog

CGlimDlg::CGlimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_ImageCtrl);
	DDX_Control(pDX, IDC_EDIT_X1, m_EditX1);
	DDX_Control(pDX, IDC_EDIT_Y1, m_EditY1);
	DDX_Control(pDX, IDC_EDIT_X2, m_EditX2);
	DDX_Control(pDX, IDC_EDIT_Y2, m_EditY2);
}

BEGIN_MESSAGE_MAP(CGlimDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CGlimDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CGlimDlg::OnBnClickedAction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CGlimDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDOK, &CGlimDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGlimDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CGlimDlg::OnInitDialog()
{
	CRect rc(0, 0, 0, 0);
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rc);
	SetDlgItemInt(IDC_EDIT_X1, rc.CenterPoint().x);
	SetDlgItemInt(IDC_EDIT_X2, rc.right);
	SetDlgItemInt(IDC_EDIT_Y1, rc.CenterPoint().y);
	SetDlgItemInt(IDC_EDIT_Y2, rc.bottom);
	return TRUE;
}

void CGlimDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CGlimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlimDlg::DrawCircle(CDC* pDC, int x, int y, int radius)
{
	CRect rc(0, 0, 0, 0);
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rc);
	pDC->FillSolidRect(rc, RGB(0, 0, 0));
	pDC->Ellipse(x - radius, y - radius, x + radius, y + radius);
}

void CGlimDlg::SaveBitmap(CDC* pDC, CRect rect, CString filename)
{
	CBitmap bitmap;
	CClientDC clientDC(GetDlgItem(IDC_STATIC_IMAGE));
	CDC memDC;
	memDC.CreateCompatibleDC(&clientDC);

	bitmap.CreateCompatibleBitmap(&clientDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);
	CImage image;
	image.Attach((HBITMAP)bitmap.Detach());
	image.Save(filename);
	memDC.SelectObject(pOldBitmap);
}

void CGlimDlg::LoadImage(CString filename)
{
	CImage image;
	image.Load(filename);
	CClientDC dc(this);
	CRect rect;
	m_ImageCtrl.GetClientRect(&rect);
	CDC* pDC = m_ImageCtrl.GetDC();
	image.Draw(pDC->m_hDC, rect);
	m_ImageCtrl.ReleaseDC(pDC);
}

void CGlimDlg::OnBnClickedDraw()
{
	CString strX1, strY1;
	m_EditX1.GetWindowText(strX1);
	m_EditY1.GetWindowText(strY1);
	int x1 = _ttoi(strX1);
	int y1 = _ttoi(strY1);
	int radius = rand() % 50 + 10;

	CClientDC dc(GetDlgItem(IDC_STATIC_IMAGE));
	DrawCircle(&dc, x1, y1, radius);
}

void CGlimDlg::OnBnClickedAction()
{
	CString strX1, strY1, strX2, strY2;
	m_EditX1.GetWindowText(strX1);
	m_EditY1.GetWindowText(strY1);
	m_EditX2.GetWindowText(strX2);
	m_EditY2.GetWindowText(strY2);
	int x1 = _ttoi(strX1);
	int y1 = _ttoi(strY1);
	int x2 = _ttoi(strX2);
	int y2 = _ttoi(strY2);

	CClientDC dc(GetDlgItem(IDC_STATIC_IMAGE));
	CRect rect;
	m_ImageCtrl.GetClientRect(&rect);
	int radius = rand() % 50 + 10;

	int dx = (x2 - x1) / 10;
	int dy = (y2 - y1) / 10;
	
	CreateDirectory(_T("image"), NULL);

	for (int i = 0; i <= 10; ++i)
	{
		int x = x1 + i * dx;
		int y = y1 + i * dy;

		Invalidate();
		UpdateWindow();
		DrawCircle(&dc, x, y, radius);

		CString filename;
		filename.Format(_T("image\\frame%02d.jpg"), i);
		SaveBitmap(&dc, rect, filename);
	}
}

void CGlimDlg::OnBnClickedOpen()
{
	CPoint ptCenter(0, 0);
	CRect rcRegion(0, 0, 0, 0);
	CRect rc(0, 0, 0, 0);
	CFileDialog dlg(TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST, _T("Image Files (*.jpg;*.bmp)|*.jpg;*.bmp|All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		CString filename = dlg.GetPathName();
		LoadImage(filename);
		CString strX1, strY1;
		m_EditX1.GetWindowText(strX1);
		m_EditY1.GetWindowText(strY1);
		int x1 = _ttoi(strX1);
		int y1 = _ttoi(strY1);
		m_ImageCtrl.GetClientRect(rc);
		rcRegion.SetRect(rc.right, rc.bottom, rc.left, rc.top);
		FindCircleCenter(filename, ptCenter, rcRegion);

		CClientDC dc(GetDlgItem(IDC_STATIC_IMAGE));
		CRect rect;
		m_ImageCtrl.GetClientRect(&rect);
		CDC* pDC = m_ImageCtrl.GetDC();
		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->MoveTo(ptCenter.x - 10, ptCenter.y);
		pDC->LineTo(ptCenter.x + 10, ptCenter.y);
		pDC->MoveTo(ptCenter.x, ptCenter.y - 10);
		pDC->LineTo(ptCenter.x, ptCenter.y + 10);

		CString strCoords;
		strCoords.Format(_T("(%d, %d)"), ptCenter.x, ptCenter.y);
		pDC->TextOutW(ptCenter.x - rcRegion.Width()/4, ptCenter.y+10, strCoords);

		pDC->SelectObject(pOldPen);
		m_ImageCtrl.ReleaseDC(pDC);
	}
}

void CGlimDlg::FindCircleCenter(CString filename, CPoint &center, CRect &rcCircle)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(filename);
	int width = bitmap->GetWidth();
	int height = bitmap->GetHeight();

	int sumX = 0, sumY = 0, count = 0;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Gdiplus::Color color;
			bitmap->GetPixel(x, y, &color);
			if (color.GetRed() > 0 && color.GetGreen() > 0 && color.GetBlue() > 0)
			{
				if (rcCircle.left > x)
					rcCircle.left = x;

				if (rcCircle.right < x)
					rcCircle.right = x;

				if (rcCircle.top > y)
					rcCircle.top = y;

				if (rcCircle.bottom < y)
					rcCircle.bottom = y;

				sumX += x;
				sumY += y;
				count++;
			}
		}
	}

	if (count > 0)
	{
		center.x = sumX / count;
		center.y = sumY / count;
	}
	else
	{
		center.x = -1;
		center.y = -1;
	}

	delete bitmap;
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

void CGlimDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CGlimDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
