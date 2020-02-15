
// SimpleMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleMFC.h"
#include "SimpleMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	WCHAR pFileName[MAX_PATH];
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CSimpleMFCDlg 对话框



CSimpleMFCDlg::CSimpleMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SIMPLEMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, mEdit);
}

BEGIN_MESSAGE_MAP(CSimpleMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSimpleMFCDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CSimpleMFCDlg::OnBnClickedButtonAbout)
END_MESSAGE_MAP()


// CSimpleMFCDlg 消息处理程序

BOOL CSimpleMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mEdit.SetWindowTextW(L"请打开一个文本文档。");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSimpleMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSimpleMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSimpleMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimpleMFCDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter = L"文件 (*.txt)|*.txt||";   //文件过虑的类型  
	CFileDialog openFileDlg(TRUE, _T("txt"), NULL, 0, filter, this);

	if (openFileDlg.DoModal() == IDOK) {
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");

		CString filePathName = openFileDlg.GetPathName();
		CStdioFile file(filePathName, CFile::modeRead | CFile::shareDenyWrite);
		CString content;
		CString line;
		while (file.ReadString(line))
			content += line + L"\r\n";
		file.Close();

		setlocale(LC_CTYPE, old_locale); //还原语言区域的设置
		free(old_locale);//还原区域设定 

		mEdit.SetWindowText(content);
	}
}


void CSimpleMFCDlg::OnBnClickedButtonAbout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//读取about.txt，设置说明文字
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ABOUT_TEXT);
	CString fileName = GetModuleDir() + L"\\about.txt";
	DWORD dwAttrib = GetFileAttributes(fileName);
	if (INVALID_FILE_ATTRIBUTES == dwAttrib || 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) //文件不存在
	{
		pEdit->SetWindowTextW(L"心好累，不管了...");
	}
	else {
		char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
		setlocale(LC_CTYPE, "chs");

		CStdioFile file(fileName, CFile::modeRead | CFile::shareDenyWrite);
		CString content;
		CString line;
		while (file.ReadString(line))
			content += line + L"\r\n";
		file.Close();

		setlocale(LC_CTYPE, old_locale); //还原语言区域的设置
		free(old_locale);//还原区域设定 
		pEdit->SetWindowTextW(content);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
