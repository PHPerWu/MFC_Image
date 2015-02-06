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
	HBITMAP HBM;

	HBM=(HBITMAP)LoadImage(NULL,L"F:\\MyProgram/CPP/MFC_Image/MFC_Image/MFC_Image/img/GEM.bmp" ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION); 
	
	BITMAP bitmap;
	GetObject(HBM,sizeof(bitmap),&bitmap);
	DeleteObject(HBM);
	X_image=bitmap.bmWidth;
	Y_image=bitmap.bmHeight;

	//��ʼ��ˮƽ���������
	xScrollMax=max(X_image-rect.Width(),0);
	scroll.cbSize=sizeof(scroll);
	scroll.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
	scroll.nMin=xScrollMin;
	scroll.nMax=X_image;
	scroll.nPage=rect.Width();
	scroll.nPos=0;
	SetScrollInfo(SB_HORZ,&scroll,TRUE);

	//��ʼ����ֱ���������
	yScrollMax=max(Y_image-rect.Height(),0);
	scroll.cbSize=sizeof(scroll);
	scroll.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
	scroll.nMin=yScrollMin;
	scroll.nMax=Y_image;
	scroll.nPage=rect.Height();
	scroll.nPos=0;
	SetScrollInfo(SB_VERT,&scroll,TRUE);

	return TRUE;
}

void CPreviewDlg::OnPaint()
{
	CPaintDC dc(this);
	CDC MemDC;

	HBITMAP HBM;
	MemDC.CreateCompatibleDC(0);
	HBM=(HBITMAP)LoadImage(NULL,L"F:\\MyProgram/CPP/MFC_Image/MFC_Image/MFC_Image/img/GEM.bmp" ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION); 

	BITMAP bitmap;

	GetObject(HBM,sizeof(bitmap),&bitmap);
	SelectObject(MemDC,HBM);
	DeleteObject(HBM);
	//��ʾͼ��
	BitBlt(dc,-xCurrentScroll,-yCurrentScroll,bitmap.bmWidth,bitmap.bmHeight,MemDC,0,0,SRCCOPY);


}

//ˮƽ������������
void CPreviewDlg::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
	int xDelta;
	int yDelta=0;

	xCurrentScroll=GetScrollPos(SB_HORZ);

	switch(nSBCode)
	{
		//�����Ϸ���ļ�ͷ�����ʱ����ǰ����λ���Լ�20
	case SB_PAGEUP:
			xCurrentScroll-=20;
			break;
	case SB_PAGEDOWN:
		xCurrentScroll+=20;
		break;
		//�������Ϸ��հ����򱻵���ʱ����ǰ����λ���Լ�5
	case SB_LINELEFT:
		xCurrentScroll-=5;
		break;
		//�������·��հ����򱻵���ʱ����ǰ����λ������5
	case SB_LINERIGHT:
		xCurrentScroll+=5;
		break;
		//�����鱻�϶�ʱ������λ�õ����϶�����������
	case SB_THUMBPOSITION:
		xCurrentScroll=nPos;
		break;
	case SB_THUMBTRACK:
		xCurrentScroll=nPos;
		break;
	default:;

	}

	//�������ķ�Χ�����˱߽磬������
	xCurrentScroll=max(0,xCurrentScroll);
	xCurrentScroll=min(xScrollMax,xCurrentScroll);
	//��������λ��δ�ı��򷵻�
	if(xCurrentScroll==GetScrollPos(SB_HORZ))
		return;

	//����ƫ�������ڻ���ԭλ�ú͵�ǰλ�õĲ�
	xDelta=xCurrentScroll-GetScrollPos(SB_HORZ);

	ScrollWindowEx(-xDelta,-yDelta,NULL,NULL,NULL,(LPRECT)NULL,SW_INVALIDATE);
	UpdateWindow();
	//���»����λ��
	SetScrollPos(SB_HORZ,xCurrentScroll,TRUE);
	//����
	CDialog::OnHScroll(nSBCode,nPos,pScrollBar);

}
//��ֱ������������
void CPreviewDlg::OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
	int xDelta=0;
	int yDelta;
	int yNewPos;

	yCurrentScroll=GetScrollPos(SB_VERT);

	switch(nSBCode)
	{
		//�����Ϸ���ļ�ͷ�����ʱ����ǰ����λ���Լ�20
	case SB_PAGEUP:
			yNewPos=yCurrentScroll-20;
			break;
	case SB_PAGEDOWN:
		yNewPos=yCurrentScroll+20;
		break;
		//�������Ϸ��հ����򱻵���ʱ����ǰ����λ���Լ�5
	case SB_LINELEFT:
		yNewPos=yCurrentScroll-5;
		break;
		//�������·��հ����򱻵���ʱ����ǰ����λ������5
	case SB_LINERIGHT:
		yNewPos=yCurrentScroll+5;
		break;
		//�����鱻�϶�ʱ������λ�õ����϶�����������
	case SB_THUMBPOSITION:
		yNewPos=nPos;
		break;
	case SB_THUMBTRACK:
		yNewPos=nPos;
		break;
	default:
		yNewPos=yCurrentScroll;

	}

	//�������ķ�Χ�����˱߽磬������
	yNewPos=max(0,yNewPos);
	yNewPos=min(yScrollMax,yNewPos);
	//��������λ��δ�ı��򷵻�
	if(yNewPos==yCurrentScroll)
		return;

	//����ƫ�������ڻ���ԭλ�ú͵�ǰλ�õĲ�
	yDelta=yNewPos-yCurrentScroll;
	yCurrentScroll=yNewPos;

	ScrollWindowEx(-xDelta,-yDelta,NULL,NULL,NULL,(LPRECT)NULL,SW_INVALIDATE);
	UpdateWindow();
	//���»����λ��
	SetScrollPos(SB_HORZ,yCurrentScroll,TRUE);
	//����
	CDialog::OnVScroll(nSBCode,nPos,pScrollBar);

}
