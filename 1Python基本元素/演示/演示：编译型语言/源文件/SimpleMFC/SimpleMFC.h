
// SimpleMFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimpleMFCApp: 
// �йش����ʵ�֣������ SimpleMFC.cpp
//

class CSimpleMFCApp : public CWinApp
{
public:
	CSimpleMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimpleMFCApp theApp;