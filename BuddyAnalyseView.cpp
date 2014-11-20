
// BuddyAnalyseView.cpp : CBuddyAnalyseView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBuddyAnalyseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBuddyAnalyseView ����/����

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBuddyAnalyseView ����

void CBuddyAnalyseView::OnDraw(CDC* /*pDC*/)
{
	CBuddyAnalyseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CBuddyAnalyseView ��ӡ


void CBuddyAnalyseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBuddyAnalyseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CBuddyAnalyseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CBuddyAnalyseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CBuddyAnalyseView ���

#ifdef _DEBUG
void CBuddyAnalyseView::AssertValid() const
{
	CView::AssertValid();
}

void CBuddyAnalyseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBuddyAnalyseDoc* CBuddyAnalyseView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBuddyAnalyseDoc)));
	return (CBuddyAnalyseDoc*)m_pDocument;
}
#endif //_DEBUG


// CBuddyAnalyseView ��Ϣ�������

void CBuddyAnalyseView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	if (m_pGrid == NULL)
	{
		//����GridCtrl����
		m_pGrid = new CGridCtrl();
		if (!m_pGrid)
			return;

		//����GridCtrl����
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

		//����к���
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
