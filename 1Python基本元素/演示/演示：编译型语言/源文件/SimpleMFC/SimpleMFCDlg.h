
// SimpleMFCDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSimpleMFCDlg 对话框
class CSimpleMFCDlg : public CDialogEx
{
// 构造
public:
	CSimpleMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLEMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit mEdit;
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonAbout();
};
