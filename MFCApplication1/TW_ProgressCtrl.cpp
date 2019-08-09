// TW_ProgressCtrl.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "TW_ProgressCtrl.h"


// TW_ProgressCtrl

IMPLEMENT_DYNAMIC(TW_ProgressCtrl, CWnd)

TW_ProgressCtrl::TW_ProgressCtrl()
{
	m_pos = 0;
	m_min = 0;
	m_max = 100;

	m_bk_color = RGB(0, 80, 160);
	m_fore_color = RGB(0, 160, 255);
}

TW_ProgressCtrl::~TW_ProgressCtrl()
{
}

void TW_ProgressCtrl::CreateProgress(CWnd * ap_parent, CRect a_rect, int a_ctrl_id) {
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE /*| WS_BORDER*/, a_rect, ap_parent, a_ctrl_id);
}

void TW_ProgressCtrl::CreateProgress(CWnd * ap_parent, int a_guide_ctrl_id, int a_ctrl_id) {
	CRect r;
	ap_parent->GetDlgItem(a_guide_ctrl_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);
	CreateProgress(ap_parent, r, a_ctrl_id);
}

void TW_ProgressCtrl::SetRange(int a_min, int a_max) {
	if (a_min == a_max) return;
	if (a_max < m_min) {
		m_max = a_min;
		m_min = a_max;
	}
	m_max = a_max;
	m_min = a_min;
}

void TW_ProgressCtrl::SetPos(int a_pos) {
	m_pos = a_pos;
	if (m_min > a_pos) m_pos = m_min;
	else if (m_max < a_pos) m_pos = m_max;
}

int TW_ProgressCtrl::GetPos() {
	return m_pos;
}

void TW_ProgressCtrl::UpdatePos(int a_pos) {
	SetPos(a_pos);
	InvalidateRect(FALSE);
}

void TW_ProgressCtrl::SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
{
	m_bk_color = a_bk_color;
	m_fore_color = a_fore_color;
}

BEGIN_MESSAGE_MAP(TW_ProgressCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void TW_ProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CDC* p_dc = m_mem_image.GetDC();

	int pos = m_pos * (m_width-2) / (m_max - m_min);

	CBrush fill_brush1(m_bk_color), fill_brush2(m_fore_color);
	CPen border_pen1(PS_SOLID, 1, m_bk_color), border_pen2(PS_SOLID, 1, m_fore_color);

	CBrush * p_old_brush = p_dc->SelectObject(&fill_brush1);
	CPen * p_old_pen = p_dc->SelectObject(&border_pen2);
	p_dc->Rectangle(0, 0, m_width, m_height);

	p_dc->SelectObject(&fill_brush2);
	p_dc->SelectObject(&border_pen1);
	p_dc->Rectangle(1, 1, pos, m_height-1);

	dc.SelectObject(p_old_brush);
	dc.SelectObject(p_old_pen);

	fill_brush1.DeleteObject();
	fill_brush2.DeleteObject();
	border_pen1.DeleteObject();
	border_pen2.DeleteObject();

	CString str;
	str.Format(L"%d", m_pos);
	p_dc->SetBkMode(TRANSPARENT);
	if (pos < m_width / 2) {
		p_dc->SetTextColor(m_fore_color);
		p_dc->DrawText(str, CRect(pos, 0, m_width, m_height), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		p_dc->SetTextColor(m_bk_color);
		p_dc->DrawText(str, CRect(0, 0, pos, m_height), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	//p_dc->FillSolidRect(0, 0, m_width, m_height, m_bk_color);
	//p_dc->FillSolidRect(1, 1, pos, m_height-2, m_fore_color);

	m_mem_image.Draw(&dc, 0, 0);
					 
}


int TW_ProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	CRect r;
	GetClientRect(r);

	m_width = r.Width();
	m_height = r.Height();

	m_mem_image.Create(this, m_width, m_height);

	return 0;
}
