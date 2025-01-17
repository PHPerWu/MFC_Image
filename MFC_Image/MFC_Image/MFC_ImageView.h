
// MFC_ImageView.h : CMFC_ImageView 类的接口
//

#pragma once


class CMFC_ImageView : public CView
{
protected: // 仅从序列化创建
	CMFC_ImageView();
	DECLARE_DYNCREATE(CMFC_ImageView)

// 特性
public:
	CMFC_ImageDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFC_ImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFC_ImageView.cpp 中的调试版本
inline CMFC_ImageDoc* CMFC_ImageView::GetDocument() const
   { return reinterpret_cast<CMFC_ImageDoc*>(m_pDocument); }
#endif

