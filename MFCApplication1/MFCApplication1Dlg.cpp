
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MY_PROGRESS, m_my_progress);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.@

	//m_my_progress.SetRange(0, 200);
	SetTimer(1, 50, NULL);

	//GetDlgItem(IDC_USER_RECT)->GetWindowRect(m_user_rect);
	//ScreenToClient(m_user_rect);

	m_user_progress.Create(this, IDC_USER_RECT);
	m_user_progress.SetRange(0, 200);
	m_user_progress.SetColor(RGB(160, 50, 0), RGB(255, 220, 0));

	m_test_progress.CreateProgress(this, IDC_USER_RECT2, 25001);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		int pos = m_my_progress.GetPos()*2;
		dc.FillSolidRect(pos, 0, 100*2, 30, RGB(0,80,160));
		dc.FillSolidRect(0, 0, pos, 30, RGB(0, 80, 255));

		//pos = m_my_progress.GetPos() * m_user_rect.Width()/100;
		//dc.FillSolidRect(m_user_rect.left+pos, m_user_rect.top, m_user_rect.Width(), m_user_rect.Height(), RGB(0, 80, 160));
		//dc.FillSolidRect(m_user_rect.left, m_user_rect.top, pos, m_user_rect.Height(), RGB(0, 80, 255));

		m_user_progress.Draw(&dc);

		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		int pos = m_my_progress.GetPos();
		pos = (pos + 1) % 101;
		m_my_progress.SetPos(pos);
		InvalidateRect(CRect(0,0,100*2,30),0);
		//InvalidateRect(m_user_rect, 0);
		//m_user_progress.SetPos(pos);
		//m_user_progress.Update(this);
		m_user_progress.Update(this, pos);

		m_test_progress.UpdatePos(pos);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCApplication1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}


int CMFCApplication1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

	

	return 0;
}
