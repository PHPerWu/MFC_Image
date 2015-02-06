
// MFC_ImageView.h : CMFC_ImageView ��Ľӿ�
//

#pragma once


class CMFC_ImageView : public CView
{
protected: // �������л�����
	CMFC_ImageView();
	DECLARE_DYNCREATE(CMFC_ImageView)

// ����
public:
	CMFC_ImageDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFC_ImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void onShowByZiYuan();
	afx_msg void OnShowFromWenJian();

	afx_msg void OnPreview();
};

#ifndef _DEBUG  // MFC_ImageView.cpp �еĵ��԰汾
inline CMFC_ImageDoc* CMFC_ImageView::GetDocument() const
   { return reinterpret_cast<CMFC_ImageDoc*>(m_pDocument); }
#endif

