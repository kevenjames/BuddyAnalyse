
// BuddyAnalyseView.cpp : CBuddyAnalyseView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "BuddyAnalyse.h"
#endif

#include "BuddyAnalyseDoc.h"
#include "BuddyAnalyseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBuddyAnalyseView

IMPLEMENT_DYNCREATE(CBuddyAnalyseView, CView)

BEGIN_MESSAGE_MAP(CBuddyAnalyseView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBuddyAnalyseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBuddyAnalyseView 构造/析构

CBuddyAnalyseView::CBuddyAnalyseView()
{
	m_pGrid = NULL;
}

CBuddyAnalyseView::~CBuddyAnalyseView()
{
	if (m_pGrid)
		delete m_pGrid;
}

BOOL CBuddyAnalyseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CBuddyAnalyseView 绘制

void CBuddyAnalyseView::OnDraw(CDC* /*pDC*/)
{
	CBuddyAnalyseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CBuddyAnalyseView 打印


void CBuddyAnalyseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBuddyAnalyseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBuddyAnalyseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBuddyAnalyseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CBuddyAnalyseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBuddyAnalyseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBuddyAnalyseView 诊断

#ifdef _DEBUG
void CBuddyAnalyseView::AssertValid() const
{
	CView::AssertValid();
}

void CBuddyAnalyseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBuddyAnalyseDoc* CBuddyAnalyseView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBuddyAnalyseDoc)));
	return (CBuddyAnalyseDoc*)m_pDocument;
}
#endif //_DEBUG


// CBuddyAnalyseView 消息处理程序

void CBuddyAnalyseView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if (m_pGrid == NULL)
	{
		//创建GridCtrl对象
		m_pGrid = new CGridCtrl();
		if (!m_pGrid)
			return;

		//创建GridCtrl窗口
		CRect rect;
		GetClientRect(rect);
		m_pGrid->Create(rect, this, 100);

		m_pGrid->SetEditable(TRUE);
		m_pGrid->EnableDragAndDrop(TRUE);

		try
		{
			m_pGrid->SetRowCount(50);
			m_pGrid->SetColumnCount(10);
			m_pGrid->SetFixedRowCount(2);
			m_pGrid->SetFixedColumnCount(3);
		}
		catch( CMemoryException* e )
		{
			e->ReportError();
			e->Delete();
			return;
		}

		//填充行和列
		for (int row = 0; row < m_pGrid->GetRowCount(); row++)
		{
			for (int col = 0; col < m_pGrid->GetColumnCount(); col++)
			{
				GV_ITEM item;
				item.mask = GVIF_TEXT | GVIF_FORMAT;
				item.row = row;
				item.col = col;
				if (row < 1)
				{
					item.nFormat = DT_LEFT | DT_WORDBREAK;
					item.szText.Format(_T("Column %d"), col);
				}
				else if (col < 1)
				{
					item.nFormat = DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					item.szText.Format(_T("Row %d"), row);
				}
				else
				{
					item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					item.szText.Format(_T("%d"), row*col);
				}
				m_pGrid->SetItem(&item);
			}
		}

		m_pGrid->AutoSize();
		m_pGrid->SetRowHeight(0, 3*m_pGrid->GetRowHeight(0)/2);
	}
}

void CBuddyAnalyseView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_pGrid->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		m_pGrid->MoveWindow(rect);
	}
}
BOOL CBuddyAnalyseView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    if (m_pGrid && IsWindow(m_pGrid->m_hWnd))
        if (m_pGrid->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
            return TRUE;

	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
void CBuddyAnalyseView::OnToggleReadonly()
{
    if (m_pGrid && IsWindow(m_pGrid->m_hWnd))
    {
        CCellID cell = m_pGrid->GetFocusCell();
        if (m_pGrid->IsValid(cell))
        {
            int nState = m_pGrid->GetItemState(cell.row, cell.col);
            if (m_pGrid->IsCellEditable(cell))
                m_pGrid->SetItemState(cell.row, cell.col, nState | GVIS_READONLY);
            else
                m_pGrid->SetItemState(cell.row, cell.col, nState & ~GVIS_READONLY);
        }
    }
}
