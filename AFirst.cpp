// AFirst.cpp: 实现文件
//

#include "pch.h"
#include "War.h"
#include "afxdialogex.h"
#include "AFirst.h"


// AFirst 对话框

IMPLEMENT_DYNAMIC(AFirst, CDialogEx)

AFirst::AFirst(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

AFirst::~AFirst()
{
}

void AFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AFirst, CDialogEx)
	ON_BN_CLICKED(IDOK, &AFirst::OnBnClickedOk)
END_MESSAGE_MAP()


// AFirst 消息处理程序


void AFirst::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
