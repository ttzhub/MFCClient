
// MFCClientDlg.h: 头文件
//

#pragma once
#include "CClient.h"

class CClient;

// CMFCClientDlg 对话框
class CMFCClientDlg : public CDialogEx
{
// 构造
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
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
	// Ip控件
	CEdit m_Ctrl_EditIp;
	// Ip控件值
	CString m_Val_EditIp;
	// Port控件值
	UINT m_Val_EditPort;
	// 发送编辑框控件
	CEdit m_Ctrl_EditSend;
	CString m_Val_EditSend;
	// 显示编辑框控件
	CEdit m_Ctrl_EditShow;
	// Client客户端
	CClient * m_Client;// 相互跨类的定义为指针，且需要在类定义前声明另一类，否则编译出错
					   // 收数处理函数
	bool ReceiveData(CClient * pServer);
	// 发送函数
	bool SendMsg();
	// 更新显示编辑框
	int UpdateEditShow(CString s);
	afx_msg void OnBnClickedBntconnect();
	afx_msg void OnBnClickedBntsend();
	// 连接标志
	bool m_flg_Connect;
	// 连接按钮控件
	CButton m_Ctrl_BntConnect;
};
