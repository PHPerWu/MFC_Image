
// MFC_ImageView.cpp : CMFC_ImageView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC_ImageView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFC_ImageView::onShowByZiYuan)
	ON_COMMAND(ID_32772, &CMFC_ImageView::OnShowFromWenJian)
	ON_COMMAND(ID_32773, &CMFC_ImageView::On32773)
END_MESSAGE_MAP()

// CMFC_ImageView ����/����

CMFC_ImageView::CMFC_ImageView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFC_ImageView::~CMFC_ImageView()
{
}

BOOL CMFC_ImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFC_ImageView ����

void CMFC_ImageView::OnDraw(CDC* /*pDC*/)
{
	CMFC_ImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
}


// CMFC_ImageView ��ӡ


void CMFC_ImageView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC_ImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFC_ImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFC_ImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMFC_ImageView ���

#ifdef _DEBUG
void CMFC_ImageView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ImageDoc* CMFC_ImageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ImageDoc)));
	return (CMFC_ImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ImageView ��Ϣ�������


void CMFC_ImageView::onShowByZiYuan()
{
	// TODO: �ڴ���������������
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);

	CRect rc;
	GetWindowRect(&rc);
	CClientDC dc(this);		//ȡ�ÿͻ����ڴ�dc

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
	// TODO: �ڴ���������������
	CClientDC dc(this);		//ȡ�ÿͻ����ڴ�dc

	CDC MemDC;

	HBITMAP HBM;
	MemDC.CreateCompatibleDC(0);
	HBM=(HBITMAP)LoadImage(NULL,L"F:\\MyProgram/CPP/MFC_Image/MFC_Image/MFC_Image/img/GEM.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);//����λͼ


	BITMAP bitmap;
	GetObject(HBM,sizeof(bitmap),&bitmap);//ȡ��λͼ��Ϣ

	SelectObject(MemDC,HBM);//ѡ��λͼ���ڴ�DC
	DeleteObject(HBM);//ɾ��λͼ
	//����ʱ�ڴ�DC�е�λͼ����
	BitBlt(dc,0,0,bitmap.bmWidth,bitmap.bmHeight,MemDC,0,0,SRCCOPY);
	
}


//void CMFC_ImageView::On32773()
//{
//	// TODO: �ڴ���������������
//	//CPreviewDlg dlg;
//	//dlg.DoModal();
//}
