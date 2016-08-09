
// CompilerEditor1.1Dlg.cpp : 实现文件
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

// 编译器部分
struct pcdata p;
static symbol* symtab[MAX];
bool ifLex = false;
bool ifParse = false;

// 文件部分
bool ifFileOpen = false;
CString openedFilePath = "";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCompilerEditor11Dlg 对话框



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


// CCompilerEditor11Dlg 消息处理程序

BOOL CCompilerEditor11Dlg::OnInitDialog()
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

	// 设置菜单
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	// 初始化编译器状态
	struct pcdata pt = { NULL, NULL, NULL, "" };
	memcpy(&p, &pt, sizeof(struct pcdata));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCompilerEditor11Dlg::OnPaint()
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
	// 获取文本框中的内容
	CEdit* codeArea = (CEdit*)this->GetDlgItem(IDC_EDIT_CODE);
	CString codes;
	codeArea->GetWindowText(codes);

#ifdef DEBUG
	// 查看获取的内容是否正确
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


	// 获取token stream
	yy_switch_to_buffer(yy_scan_string((LPCSTR)(LPCTSTR)codes, p.scaninfo), p.scaninfo);
	yyparse(&p);


	ofstream tokensOut("tokens.txt");
	tokensOut << p.tokens << endl;
	tokensOut << p.tokens.size() << endl;
	tokensOut.close();

	// 输出至输出框内
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
	// TODO:  在此添加命令处理程序代码
	//yyparse(&p);

	// 画树
	TreeDrawer td;
	if (p.ast)
	{
		// 在output里面文字输出一棵树
		/*string textTree = td.printTextTree(p.ast);
		CString outputMsg = textTree.c_str();
		CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
		outputArea->SetWindowTextA(outputMsg);
		outputArea->LineScroll(outputArea->GetLineCount());
		*/
		//CEdit* outputArea = (CEdit*)this->GetDlgItem(IDC_EDIT_OUTPUTAREA);
		//outputArea->SetWindowTextA("请查看图形界面！");

		// 画图，再开一个线程防止卡死
		thread t1(ThreadProcDrawGraphicTree, p.ast);
		t1.join();
		// 其实没用
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
	// TODO:  在此添加命令处理程序代码
	if(MessageBox(LPCTSTR("确定要退出吗？"), LPCTSTR(""), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		// 向主程序发送退出消息
		AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
	}

}

void CCompilerEditor11Dlg::OnOpenfile()
{
	// TODO:  在此添加命令处理程序代码
	// 对话框，选择文件读入
	// 如果现在有文件打开着，让用户选择是否保存
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, "All Files(*.mylang)|*.mylang", NULL, 0, 1);
	CString strPath, strText = "";
	char read[10000];
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		if (strPath.Right(7) != ".mylang")
			strPath += ".mylang";

		// 在输出一栏中显示文件路径
		CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
		outputArea->SetWindowTextA("打开文件路径：" + strPath);

		CFile file(strPath, CFile::modeRead);
		int fileLength = file.GetLength();
		if (fileLength >= 10000)
		{
			outputArea->SetWindowTextA("文件" + strPath + "太长！");
			return;
		}
		file.Read(read, 10000);
		file.Close();

		for (int i = 0; i < fileLength; i++)
		{
			strText += read[i];
		}

		// 保存当前打开文档的状态
		ifFileOpen = true;
		openedFilePath = strPath;

		// 设置编辑窗口
		CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
		codeArea->SetWindowTextA(strText);
	}

}


void CCompilerEditor11Dlg::OnSavefile()
{
	// 
	if (!ifFileOpen)
	{
		// 打开文本对话框，选择保存文件的位置以及名称等
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All Files(*.mylang)|*.mylang||", NULL, 0, 1);
		CString strPath;
		if (dlg.DoModal() == IDOK)
		{
			ifFileOpen = true;
			openedFilePath = dlg.GetPathName();
		}
	}

	// 保存当前文件
	// 获取当前编辑区域内容
	CString code;
	CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
	codeArea->GetWindowTextA(code);

	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));

	// 打开当前文件位置
	CFile file(openedFilePath, CFile::modeWrite | CFile::modeCreate);
	int codeLength = code.GetLength();
	char* buffer = new char[codeLength + 1];
	if (buffer == NULL)
	{
		outputArea->SetWindowTextA("保存文件失败！");
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

	
	outputArea->SetWindowTextA("保存文件至：" + openedFilePath);
}


void CCompilerEditor11Dlg::OnNewfile()
{
	// TODO:  在此添加命令处理程序代码
	if (ifFileOpen)
	{
		if (MessageBox("要保存当前文件吗？", "", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			OnSavefile();
		}
	}

	// 直接刷空
	CEdit* codeArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_CODE));
	codeArea->SetWindowTextA("");
	ifFileOpen = false;
	openedFilePath = "";

	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
	outputArea->SetWindowTextA("新建文件成功！");
}


void CCompilerEditor11Dlg::OnOnsaveoutput()
{
	// TODO:  在此添加命令处理程序代码
	// save the output in output.txt
	// 获取输出框内容
	CString str;
	CEdit* outputArea = (CEdit*)(this->GetDlgItem(IDC_EDIT_OUTPUTAREA));
	outputArea->GetWindowTextA(str);

	// 
	int length = str.GetLength();
	char* output = new char[length];
	if (output == NULL)
	{
		outputArea->SetWindowTextA("保存文件失败！");
		return;
	}

	for (int i = 0; i < length; i++)
		output[i] = str.GetAt(i);

	CFile file("OutputArea.txt", CFile::modeWrite | CFile::modeCreate);
	file.Write(output, length);
	file.Close();
	
	outputArea->SetWindowTextA("保存输出至OutputArea.txt中");

}
