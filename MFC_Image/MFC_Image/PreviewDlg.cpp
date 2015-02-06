// PreviewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_Image.h"
#include "PreviewDlg.h"
#include "afxdialogex.h"


// CPreviewDlg 对话框
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


// CPreviewDlg 消息处理程序
//对话框的初始化函数
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

	//载入图片
	HBITMAP HBM;

	HBM=(HBITMAP)LoadImage(NULL,L"F:\\MyProgram/CPP/MFC_Image/MFC_Image/MFC_Image/img/GEM.bmp" ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION); 
	
	BITMAP bitmap;
	GetObject(HBM,sizeof(bitmap),&bitmap);
	DeleteObject(HBM);
	X_image=bitmap.bmWidth;
	Y_image=bitmap.bmHeight;

	//初始化水平方向滚动条
	xScrollMax=max(X_image-rect.Width(),0);
	scroll.cbSize=sizeof(scroll);
	scroll.fMask=SIF_RANGE | SIF_PAGE | SIF_POS;
	scroll.nMin=xScrollMin;
	scroll.nMax=X_image;
	scroll.nPage=rect.Width();
	scroll.nPos=0;
	SetScrollInfo(SB_HORZ,&scroll,TRUE);

	//初始化垂直方向滚动条
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
	//显示图像
	BitBlt(dc,-xCurrentScroll,-yCurrentScroll,bitmap.bmWidth,bitmap.bmHeight,MemDC,0,0,SRCCOPY);


}

//水平滚动条处理函数
void CPreviewDlg::OnHScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
	int xDelta;
	int yDelta=0;

	xCurrentScroll=GetScrollPos(SB_HORZ);

	switch(nSBCode)
	{
		//当向上方向的箭头被点击时，当前滑块位置自减20
	case SB_PAGEUP:
			xCurrentScroll-=20;
			break;
	case SB_PAGEDOWN:
		xCurrentScroll+=20;
		break;
		//当滑块上方空白区域被单击时，当前滑块位置自减5
	case SB_LINELEFT:
		xCurrentScroll-=5;
		break;
		//当滑块下方空白区域被单击时，当前滑块位置自增5
	case SB_LINERIGHT:
		xCurrentScroll+=5;
		break;
		//当滑块被拖动时，最终位置等于拖动操作结束点
	case SB_THUMBPOSITION:
		xCurrentScroll=nPos;
		break;
	case SB_THUMBTRACK:
		xCurrentScroll=nPos;
		break;
	default:;

	}

	//如果滑块的范围超过了边界，则修正
	xCurrentScroll=max(0,xCurrentScroll);
	xCurrentScroll=min(xScrollMax,xCurrentScroll);
	//如果滑块的位置未改变则返回
	if(xCurrentScroll==GetScrollPos(SB_HORZ))
		return;

	//滑块偏移量等于滑块原位置和当前位置的差
	xDelta=xCurrentScroll-GetScrollPos(SB_HORZ);

	ScrollWindowEx(-xDelta,-yDelta,NULL,NULL,NULL,(LPRECT)NULL,SW_INVALIDATE);
	UpdateWindow();
	//更新滑块的位置
	SetScrollPos(SB_HORZ,xCurrentScroll,TRUE);
	//滚屏
	CDialog::OnHScroll(nSBCode,nPos,pScrollBar);

}
//垂直滚动条处理函数
void CPreviewDlg::OnVScroll(UINT nSBCode,UINT nPos,CScrollBar* pScrollBar)
{
	int xDelta=0;
	int yDelta;
	int yNewPos;

	yCurrentScroll=GetScrollPos(SB_VERT);

	switch(nSBCode)
	{
		//当向上方向的箭头被点击时，当前滑块位置自减20
	case SB_PAGEUP:
			yNewPos=yCurrentScroll-20;
			break;
	case SB_PAGEDOWN:
		yNewPos=yCurrentScroll+20;
		break;
		//当滑块上方空白区域被单击时，当前滑块位置自减5
	case SB_LINELEFT:
		yNewPos=yCurrentScroll-5;
		break;
		//当滑块下方空白区域被单击时，当前滑块位置自增5
	case SB_LINERIGHT:
		yNewPos=yCurrentScroll+5;
		break;
		//当滑块被拖动时，最终位置等于拖动操作结束点
	case SB_THUMBPOSITION:
		yNewPos=nPos;
		break;
	case SB_THUMBTRACK:
		yNewPos=nPos;
		break;
	default:
		yNewPos=yCurrentScroll;

	}

	//如果滑块的范围超过了边界，则修正
	yNewPos=max(0,yNewPos);
	yNewPos=min(yScrollMax,yNewPos);
	//如果滑块的位置未改变则返回
	if(yNewPos==yCurrentScroll)
		return;

	//滑块偏移量等于滑块原位置和当前位置的差
	yDelta=yNewPos-yCurrentScroll;
	yCurrentScroll=yNewPos;

	ScrollWindowEx(-xDelta,-yDelta,NULL,NULL,NULL,(LPRECT)NULL,SW_INVALIDATE);
	UpdateWindow();
	//更新滑块的位置
	SetScrollPos(SB_HORZ,yCurrentScroll,TRUE);
	//滚屏
	CDialog::OnVScroll(nSBCode,nPos,pScrollBar);

}
