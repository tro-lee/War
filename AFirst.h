#pragma once
#include "afxdialogex.h"


// AFirst 对话框

class AFirst : public CDialogEx
{
	DECLARE_DYNAMIC(AFirst)

public:
	AFirst(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AFirst();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
