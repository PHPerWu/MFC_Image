#pragma once


// CPreviewDlg �Ի���

class CPreviewDlg : public CDialog
{
	DECLARE_MESSAGE_MAP();
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	int X_image;
	int Y_image;

	CPreviewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPreviewDlg();


	virtual BOOL OnInitDialog();
	virtual void OnOK() {}
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar);

// �Ի�������
	enum { IDD = IDD_PREVIEWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	
};
