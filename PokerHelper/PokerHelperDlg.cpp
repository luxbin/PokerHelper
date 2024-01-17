
// PokerHelperDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PokerHelper.h"
#include "PokerHelperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPokerHelperDlg dialog



CPokerHelperDlg::CPokerHelperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_POKERHELPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPokerHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPokerHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPokerHelperDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPokerHelperDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_JOIN, &CPokerHelperDlg::OnBnClickedBtnJoin)
END_MESSAGE_MAP()


// CPokerHelperDlg message handlers

BOOL CPokerHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitProc();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPokerHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPokerHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPokerHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void DoubleClick(int x, int y)
{
	const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
	const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

	POINT cursorPos;
	GetCursorPos(&cursorPos);

	double cx = cursorPos.x * XSCALEFACTOR;
	double cy = cursorPos.y * YSCALEFACTOR;

	double nx = x * XSCALEFACTOR;
	double ny = y * YSCALEFACTOR;

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dx = (LONG)nx;
	Input.mi.dy = (LONG)ny;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;

	SendInput(1, &Input, sizeof(INPUT));
	SendInput(1, &Input, sizeof(INPUT));

	Input.mi.dx = (LONG)cx;
	Input.mi.dy = (LONG)cy;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	SendInput(1, &Input, sizeof(INPUT));
}


void CPokerHelperDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CPokerHelperDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CPokerHelperDlg::OnBnClickedBtnJoin()
{
	JoinTable();
}

void CPokerHelperDlg::InitProc()
{

	m_pAutomation = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**)&m_pAutomation);
	if (SUCCEEDED(hr)) {

	}
}

IUIAutomationElement* CPokerHelperDlg::FindBy_UIA_NPI(IUIAutomationElement* root, std::wstring name)
{
	IUIAutomationElement* pElement = nullptr;
	IUIAutomationCondition* condition = nullptr;

	VARIANT var{};
	var.bstrVal = SysAllocStringLen(name.c_str(), name.size());
	var.vt = VT_BSTR;

	HRESULT hr = m_pAutomation->CreatePropertyCondition(UIA_LegacyIAccessibleNamePropertyId, var, &condition);
	if (FAILED(hr))
	{
		//std::cout << Error Creating Condition\n;
		return nullptr;
	}

	hr = root->FindFirst(TreeScope_Subtree, condition, &pElement);
	if (FAILED(hr))
	{
		//std::cout << Error Finding First Occurence\n;
		condition->Release();
		return nullptr;
	}

	SysFreeString(var.bstrVal);
	condition->Release();

	return pElement;
}

IUIAutomationElement* CPokerHelperDlg::FindAllBy_UIA_NPI(IUIAutomationElement* root, std::wstring name, IUIAutomationElementArray** elements)
{
	IUIAutomationElement* pElement = nullptr;
	IUIAutomationCondition* condition = nullptr;

	VARIANT var{};
	var.bstrVal = SysAllocStringLen(name.c_str(), name.size());
	var.vt = VT_BSTR;

	HRESULT hr = m_pAutomation->CreatePropertyCondition(UIA_LegacyIAccessibleNamePropertyId, var, &condition);
	if (FAILED(hr))
	{
		//std::cout << Error Creating Condition\n;
		return nullptr;
	}

	hr = root->FindAll(TreeScope_Subtree, condition, elements);
	if (FAILED(hr))
	{
		//std::cout << Error Finding First Occurence\n;
		condition->Release();
		return nullptr;
	}

	SysFreeString(var.bstrVal);
	condition->Release();

	return pElement;
}


void CPokerHelperDlg::JoinTable()
{


	HWND hWnd = ::FindWindow(L"Chrome_WidgetWin_1", L"Winamax");

	if (!hWnd) return;

	static int xx = 0;

	if (xx == 0) {
		::ShowWindow(hWnd, SW_MAXIMIZE);

		Sleep(1000);

		::ShowWindow(hWnd, SW_SHOWDEFAULT);
	}

	xx++;

	IUIAutomationElement* root = NULL;

	HRESULT hr = m_pAutomation->ElementFromHandle(hWnd, &root);

	if (root == NULL) return;

	IUIAutomationElement* baseElement = NULL;

	//baseElement = FindBy_UIA_NPI(root, L"€10-20");

	/*
	POINT pt;
	BOOL got;
	baseElement->GetClickablePoint(&pt, &got);
	DoubleClick(pt.x, pt.y);
	*/

	
	IUIAutomationElementArray* elements = nullptr;

	FindAllBy_UIA_NPI(root, L"€10-20", &elements);

	int subCount = 0;
	elements->get_Length(&subCount);

	if (subCount > 1) {
		elements->GetElement(1, &baseElement);

		POINT pt;
		BOOL got;
		baseElement->GetClickablePoint(&pt, &got);
		DoubleClick(pt.x, pt.y);
	}
	

	int x = 0;

	/*
	IUIAutomationElement* baseElement = NULL;

	baseElement = FindBy_UIA_NPI(root, L"My games");

	BSTR xxx;
	baseElement->get_CurrentName(&xxx);


	IUIAutomationElement* parentElement = nullptr;
	IUIAutomationTreeWalker* treeWalker = nullptr;
	IUIAutomationElementArray* subElements = nullptr;

	IUIAutomationCondition* condition = nullptr;
	m_pAutomation->CreateTrueCondition(&condition);
	

	m_pAutomation->get_ControlViewWalker(&treeWalker);
	treeWalker->GetParentElement(baseElement, &parentElement);

	//treeWalker->GetParentElement(parentElement, &parentElement);

	//baseElement->FindAll(TreeScope_Parent, condition, &subElements);

	IUIAutomationElement* parentElement1;

	

	treeWalker->GetParentElement(parentElement, &parentElement1);

	SAFEARRAY* sa;
	
	parentElement1->GetRuntimeId(&sa);

	

	//m_pAutomation->CreatePropertyCondition(UIA_ControlTypePropertyId, UIA_GroupControlTypeId, &condition);

	parentElement->FindAll(TreeScope_Children, condition, &subElements);


	int subCount = 0;
	subElements->get_Length(&subCount);

	int x = 0;
	*/
}
