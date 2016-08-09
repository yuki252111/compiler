
// CompilerEditor1.1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "CompilerEditor1.1.h"
#include "CompilerEditor1.1Dlg.h"
#include "afxdialogex.h"

#include "defination.h"
#include "lexer.h"
#include "parser.h"
#include "TreeDrawer.h"
#include "IRGeneration.h"

#include <thread>
#include <string>
using std::thread;
using std::string;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����������
struct pcdata p;
static symbol* symtab[MAX];
bool ifLex = false;
bool ifParse = false;

// �ļ�����
bool ifFileOpen = false;
CString openedFilePath = "";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCompilerEditor11Dlg �Ի���



CCompilerEditor11Dlg::CCompilerEditor11Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompilerEditor11Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompilerEditor11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCompilerEditor11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_LEXANALYSER, &CCompilerEditor11Dlg::OnLexAnalyser)
	ON_COMMAND(ID_PARSER, &CCompilerEditor11Dlg::OnParser)
	ON_COMMAND(ID_SEMENTICANALYSE, &CCompilerEditor11Dlg::OnSementicanalyse)
	ON_COMMAND(ID_QUITPROGRAM, &CCompilerEditor11Dlg::OnQuitprogram)
	ON_COMMAND(ID_OPENFILE, &CCompilerEditor11Dlg::OnOpenfile)
	ON_COMMAND(ID_SAVEFILE, &CCompilerEditor11Dlg::OnSavefile)
	ON_COMMAND(ID_NEWFILE, &CCompilerEditor11Dlg::OnNewfile)
	ON_COMMAND(ID_ONSAVEOUTPUT, &CCompilerEditor11Dlg::OnOnsaveoutput)
END_MESSAGE_MAP()


// CCompilerEditor11Dlg ��Ϣ�������

BOOL CCompilerEditor11Dlg::OnInitDialog()
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

	// ���ò˵�
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	// ��ʼ��������״̬
	struct pcdata pt = { NULL, NULL, NULL, "" };
	memcpy(&p, &pt, sizeof(struct pcdata));


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCompilerEditor11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCompilerEditor11Dlg::OnPaint()
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
HCURSOR CCompilerEditor11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString TranslateEnter(string str)
{
	CString ret = "";
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] != '\n')
			ret += str[i];
		else
			ret += "\r\n";
	}
	return ret;
}

void CCompilerEditor11Dlg::OnLexAnalyser()
{
	// ��ȡ�ı����е�����
	CEdit* codeArea = (CEdit*)this->GetDlgItem(IDC_EDIT_CODE);
	CString codes;
	codeArea->GetWindowText(codes);

#ifdef DEBUG
	// �鿴��ȡ�������Ƿ���ȷ
	MessageBox(codes, LPCTSTR("codes to analyze"), MB_OK);
#endif

	if (yylex_init_extra(&p, &p.scaninfo)){
		perror("init failed\n");
		MessageBox(LPCTSTR("Init failed"), LPCTSTR(""), MB_OK | MB_ICONERROR);
	}
	p.symtab = symtab;
	for (int i = 0; i < MAX; i++)
		p.symtab[i] = NULL;
	p.tokens = "";


	// ��ȡtoken stream
	yy_switch_to_buffer(yy_scan_string((LPCSTR)(LPCTSTR)codes, p.scaninfo), p.scaninfo);
	yyparse(&p);


	ofstream tokensOut("tokens.txt");
	tokensOut << p.tokens << endl;
	tokensOut << p.tokens.size() << endl;
	tokensOut.close();

	// ������������
	CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
	CString outputMsg = TranslateEnter(p.tokens);

#ifdef DEBUG
	MessageBox(outputMsg, LPCTSTR("tokens"), MB_OK);
#endif

	outputArea->SetWindowTextA(outputMsg);
	outputArea->LineScroll(outputArea->GetLineCount());
}


void ThreadProcDrawGraphicTree(ast* node)
{
	TreeDrawer ttd;
	ttd.printGraphicTree(node);
}

void CCompilerEditor11Dlg::OnParser()
{
	// TODO:  �ڴ���������������
	//yyparse(&p);

	// ����
	TreeDrawer td;
	if (p.ast)
	{
		// ��output�����������һ����
		/*string textTree = td.printTextTree(p.ast);
		CString outputMsg = textTree.c_str();
		CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
		outputArea->SetWindowTextA(outputMsg);
		outputArea->LineScroll(outputArea->GetLineCount());
		*/
		//CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
		//outputArea->SetWindowTextA("��鿴ͼ�ν��棡");

		// ��ͼ���ٿ�һ���̷߳�ֹ����
		thread t1(ThreadProcDrawGraphicTree, p.ast);
		t1.join();
		// ��ʵû��
		//td.printGraphicTree(p.ast);
	}
	else
	{
		MessageBox(LPCTSTR("Unable to create parse tree."), LPCTSTR(""), MB_OK | MB_ICONERROR);
	}
}


void CCompilerEditor11Dlg::OnSementicanalyse()
{
	if (p.ast)
	{
		IRGeneration* irg = new IRGeneration(p.ast);
		string ir = irg->Generate();
		CString outputMsg = TranslateEnter(ir);

		CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
		outputArea->SetWindowTextA(outputMsg);
		outputArea->LineScroll(outputArea->GetLineCount());
	}
}


void CCompilerEditor11Dlg::OnQuitprogram()
{
	// TODO:  �ڴ���������������
	if(MessageBox(LPCTSTR("ȷ��Ҫ�˳���"), LPCTSTR(""), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		// �����������˳���Ϣ
		AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
	}

}

void CCompilerEditor11Dlg::OnOpenfile()
{
	// TODO:  �ڴ���������������
	// �Ի���ѡ���ļ�����
	// ����������ļ����ţ����û�ѡ���Ƿ񱣴�
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, "All Files(*.mylang)|*.mylang", NULL, 0, 1);
	CString strPath, strText = "";
	char read[10000];
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if (strPath.Right(7) != ".mylang")
			strPath += ".mylang";

		// �����һ������ʾ�ļ�·��
		CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
		outputArea->SetWindowTextA("���ļ�·����" + strPath);

		CFile file(strPath, CFile::modeRead);
		int fileLength = file.GetLength();
		if (fileLength >= 10000)
		{
			outputArea->SetWindowTextA("�ļ�" + strPath + "̫����");
			return;
		}
		file.Read(read, 10000);
		file.Close();

		for (int i = 0; i < fileLength; i++)
		{
			strText += read[i];
		}

		// ���浱ǰ���ĵ���״̬
		ifFileOpen = true;
		openedFilePath = strPath;

		// ���ñ༭����
		CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
		codeArea->SetWindowTextA(strText);
	}

}


void CCompilerEditor11Dlg::OnSavefile()
{
	// 
	if (!ifFileOpen)
	{
		// ���ı��Ի���ѡ�񱣴��ļ���λ���Լ����Ƶ�
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files(*.mylang)|*.mylang||", NULL, 0, 1);
		CString strPath;
		if (dlg.DoModal() == IDOK)
		{
			ifFileOpen = true;
			openedFilePath = dlg.GetPathName();
		}
	}

	// ���浱ǰ�ļ�
	// ��ȡ��ǰ�༭��������
	CString code;
	CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
	codeArea->GetWindowTextA(code);

	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));

	// �򿪵�ǰ�ļ�λ��
	CFile file(openedFilePath, CFile::modeWrite | CFile::modeCreate);
	int codeLength = code.GetLength();
	char* buffer = new char[codeLength + 1];
	if (buffer == NULL)
	{
		outputArea->SetWindowTextA("�����ļ�ʧ�ܣ�");
		return;
	}
	for (int i = 0; i < codeLength; i++)
	{
		buffer[i] = code.GetAt(i);
	}
	buffer[codeLength] = '\0';

	file.Write(buffer, codeLength + 1);
	file.Close();
	if (buffer)
		delete buffer;

	
	outputArea->SetWindowTextA("�����ļ�����" + openedFilePath);
}


void CCompilerEditor11Dlg::OnNewfile()
{
	// TODO:  �ڴ���������������
	if (ifFileOpen)
	{
		if (MessageBox("Ҫ���浱ǰ�ļ���", "", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			OnSavefile();
		}
	}

	// ֱ��ˢ��
	CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
	codeArea->SetWindowTextA("");
	ifFileOpen = false;
	openedFilePath = "";

	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
	outputArea->SetWindowTextA("�½��ļ��ɹ���");
}


void CCompilerEditor11Dlg::OnOnsaveoutput()
{
	// TODO:  �ڴ���������������
	// save the output in output.txt
	// ��ȡ���������
	CString str;
	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
	outputArea->GetWindowTextA(str);

	// 
	int length = str.GetLength();
	char* output = new char[length];
	if (output == NULL)
	{
		outputArea->SetWindowTextA("�����ļ�ʧ�ܣ�");
		return;
	}

	for (int i = 0; i < length; i++)
		output[i] = str.GetAt(i);

	CFile file("OutputArea.txt", CFile::modeWrite | CFile::modeCreate);
	file.Write(output, length);
	file.Close();
	
	outputArea->SetWindowTextA("���������OutputArea.txt��");

}
