
// CompilerEditor1.1Dlg.h : ͷ�ļ�
//

#pragma once


// CCompilerEditor11Dlg �Ի���
class CCompilerEditor11Dlg : public CDialogEx
{
// ����
public:
	CCompilerEditor11Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMPILEREDITOR11_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CMenu m_Menu;

	// ���ɵ���Ϣӳ�亯��
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
