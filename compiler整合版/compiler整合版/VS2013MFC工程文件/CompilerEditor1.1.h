
// CompilerEditor1.1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCompilerEditor11App: 
// �йش����ʵ�֣������ CompilerEditor1.1.cpp
//

class CCompilerEditor11App : public CWinApp
{
public:
	CCompilerEditor11App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCompilerEditor11App theApp;