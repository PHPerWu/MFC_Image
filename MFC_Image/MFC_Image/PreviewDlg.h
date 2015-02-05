#pragma once


// CPreviewDlg 对话框

class CPreviewDlg : public CDialog
{
	DECLARE_MESSAGE_MAP();
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	int X_image;
	int Y_image;

	CPreviewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPreviewDlg();


	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);

// 对话框数据
	enum { IDD = IDD_PREVIEWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	
};
