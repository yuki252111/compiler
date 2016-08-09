
// CompilerEditor1.1Dlg.h : 头文件
//

#pragma once


// CCompilerEditor11Dlg 对话框
class CCompilerEditor11Dlg : public CDialogEx
{
// 构造
public:
	CCompilerEditor11Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMPILEREDITOR11_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_Menu;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLexAnalyser();
	afx_msg void OnParser();
	afx_msg void OnSementicanalyse();
	afx_msg void OnQuitprogram();
	afx_msg void OnOpenfile();
	afx_msg void OnSavefile();
	afx_msg void OnNewfile();
	afx_msg void OnOnsaveoutput();
};
