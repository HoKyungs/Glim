
// GlimDlg.h : header file
//

#pragma once


// CGlimDlg dialog
class CGlimDlg : public CDialogEx
{
// Construction
public:
	CGlimDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedDraw();
	afx_msg void OnBnClickedAction();
	afx_msg void OnBnClickedOpen();

	CStatic m_ImageCtrl;
	CEdit m_EditX1;
	CEdit m_EditY1;
	CEdit m_EditX2;
	CEdit m_EditY2;

	void FindCircleCenter(CString filename, CPoint &center, CRect &rcCircle);

	void DrawCircle(CDC* pDC, int x, int y, int radius);
	void SaveBitmap(CDC* pDC, CRect rect, CString filename);
	void LoadImage(CString filename);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
