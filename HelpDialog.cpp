// HelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "War.h"
#include "afxdialogex.h"
#include "HelpDialog.h"


// HelpDialog 对话框

IMPLEMENT_DYNAMIC(HelpDialog, CDialogEx)

HelpDialog::HelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPPAGE_MEDIUM, pParent)
{

}

HelpDialog::~HelpDialog()
{
}

void HelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDialog, CDialogEx)
END_MESSAGE_MAP()


// HelpDialog 消息处理程序
