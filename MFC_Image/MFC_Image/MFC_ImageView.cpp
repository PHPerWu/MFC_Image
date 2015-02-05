
// MFC_ImageView.cpp : CMFC_ImageView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC_Image.h"
#endif

#include "MFC_ImageDoc.h"
#include "MFC_ImageView.h"
#include "PreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_ImageView

IMPLEMENT_DYNCREATE(CMFC_ImageView, CView)

BEGIN_MESSAGE_MAP(CMFC_ImageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_ImageView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFC_ImageView::onShowByZiYuan)
	ON_COMMAND(ID_32772, &CMFC_ImageView::OnShowFromWenJian)
	ON_COMMAND(ID_32773, &CMFC_ImageView::On32773)
END_MESSAGE_MAP()

// CMFC_ImageView 构造/析构

CMFC_ImageView::CMFC_ImageView()
{
	// TODO: 在此处添加构造代码

}

CMFC_ImageView::~CMFC_ImageView()
{
}

BOOL CMFC_ImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC_ImageView 绘制

void CMFC_ImageView::OnDraw(CDC* /*pDC*/)
{
	CMFC_ImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
}


// CMFC_ImageView 打印


void CMFC_ImageView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_ImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC_ImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC_ImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFC_ImageView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC_ImageView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC_ImageView 诊断

#ifdef _DEBUG
void CMFC_ImageView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ImageDoc* CMFC_ImageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ImageDoc)));
	return (CMFC_ImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ImageView 消息处理程序


void CMFC_ImageView::onShowByZiYuan()
{
	// TODO: 在此添加命令处理程序代码
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);

	CRect rc;
	GetWindowRect(&rc);
	CClientDC dc(this);		//取得客户区内存dc

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap=MemDC.SelectObject(&bitmap);
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(5,5,rc.right-rc.left-10,rc.bottom-rc.top-80,&MemDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}


void CMFC_ImageView::OnShowFromWenJian()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC dc(this);		//取得客户区内存dc

	CDC MemDC;

	HBITMAP HBM;
	MemDC.CreateCompatibleDC(0);
	HBM=(HBITMAP)LoadImage(NULL,L"F:\\MyProgram/CPP/MFC_Image/MFC_Image/MFC_Image/img/GEM.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);//载入位图


	BITMAP bitmap;
	GetObject(HBM,sizeof(bitmap),&bitmap);//取得位图信息

	SelectObject(MemDC,HBM);//选入位图至内存DC
	DeleteObject(HBM);//删除位图
	//将临时内存DC中的位图画到
	BitBlt(dc,0,0,bitmap.bmWidth,bitmap.bmHeight,MemDC,0,0,SRCCOPY);
	
}


//void CMFC_ImageView::On32773()
//{
//	// TODO: 在此添加命令处理程序代码
//	//CPreviewDlg dlg;
//	//dlg.DoModal();
//}
