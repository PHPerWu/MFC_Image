// PreviewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_Image.h"
#include "PreviewDlg.h"
#include "afxdialogex.h"


// CPreviewDlg �Ի���
SCROLLINFO scroll;

static int yCurrentScroll;
static int yScrollMax;
static int yScrollMin;

static int xCurrentScroll;
static int xScrollMax;
static int xScrollMin;


IMPLEMENT_DYNAMIC(CPreviewDlg, CDialog)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{

}

CPreviewDlg::~CPreviewDlg()
{
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
ON_WM_PAINT()
ON_WM_HSCROLL()
ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CPreviewDlg ��Ϣ�������
//�Ի���ĳ�ʼ������
BOOL CPreviewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);

	yCurrentScroll=0;
	yScrollMax=0;
	yScrollMin=0;

	xCurrentScroll=0;
	xScrollMax=0;
	xScrollMin=0;

	//����ͼƬ
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);//����Դ�ļ��л�ȡͼƬ����������ͼƬ��ID��
	
}
