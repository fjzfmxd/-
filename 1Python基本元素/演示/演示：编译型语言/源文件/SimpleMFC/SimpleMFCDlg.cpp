
// SimpleMFCDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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



// CSimpleMFCDlg �Ի���



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


// CSimpleMFCDlg ��Ϣ�������

BOOL CSimpleMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	mEdit.SetWindowTextW(L"���һ���ı��ĵ���");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimpleMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSimpleMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimpleMFCDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filter = L"�ļ� (*.txt)|*.txt||";   //�ļ����ǵ�����  
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

		setlocale(LC_CTYPE, old_locale); //��ԭ�������������
		free(old_locale);//��ԭ�����趨 

		mEdit.SetWindowText(content);
	}
}


void CSimpleMFCDlg::OnBnClickedButtonAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ȡabout.txt������˵������
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ABOUT_TEXT);
	CString fileName = GetModuleDir() + L"\\about.txt";
	DWORD dwAttrib = GetFileAttributes(fileName);
	if (INVALID_FILE_ATTRIBUTES == dwAttrib || 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) //�ļ�������
	{
		pEdit->SetWindowTextW(L"�ĺ��ۣ�������...");
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

		setlocale(LC_CTYPE, old_locale); //��ԭ�������������
		free(old_locale);//��ԭ�����趨 
		pEdit->SetWindowTextW(content);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
