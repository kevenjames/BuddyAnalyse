
// BuddyAnalyseView.h : CBuddyAnalyseView ��Ľӿ�
//

#pragma once
#include "./Grid/GridCtrl.h"


class CBuddyAnalyseView : public CView
{
protected: // �������л�����
	CBuddyAnalyseView();
	DECLARE_DYNCREATE(CBuddyAnalyseView)

// ����
public:
	CBuddyAnalyseDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CBuddyAnalyseView();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToggleReadonly();
	DECLARE_MESSAGE_MAP()

private:
	CGridCtrl* m_pGrid;
};

#ifndef _DEBUG  // BuddyAnalyseView.cpp �еĵ��԰汾
inline CBuddyAnalyseDoc* CBuddyAnalyseView::GetDocument() const
   { return reinterpret_cast<CBuddyAnalyseDoc*>(m_pDocument); }
#endif

