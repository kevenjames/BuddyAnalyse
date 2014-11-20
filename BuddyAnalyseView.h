
// BuddyAnalyseView.h : CBuddyAnalyseView 类的接口
//

#pragma once
#include "./Grid/GridCtrl.h"


class CBuddyAnalyseView : public CView
{
protected: // 仅从序列化创建
	CBuddyAnalyseView();
	DECLARE_DYNCREATE(CBuddyAnalyseView)

// 特性
public:
	CBuddyAnalyseDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CBuddyAnalyseView();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToggleReadonly();
	DECLARE_MESSAGE_MAP()

private:
	CGridCtrl* m_pGrid;
};

#ifndef _DEBUG  // BuddyAnalyseView.cpp 中的调试版本
inline CBuddyAnalyseDoc* CBuddyAnalyseView::GetDocument() const
   { return reinterpret_cast<CBuddyAnalyseDoc*>(m_pDocument); }
#endif

