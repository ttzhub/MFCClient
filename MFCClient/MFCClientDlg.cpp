
// MFCClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClientDlg 对话框



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
	, m_Val_EditIp(_T("127.0.0.1"))
	, m_Val_EditPort(1111)
	, m_Val_EditSend(_T(""))
	, m_flg_Connect(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EditIp, m_Ctrl_EditIp);
	DDX_Text(pDX, IDC_EditIp, m_Val_EditIp);
	DDX_Text(pDX, IDC_EditPort, m_Val_EditPort);
	DDX_Control(pDX, IDC_EDIT4, m_Ctrl_EditSend);
	DDX_Text(pDX, IDC_EDIT4, m_Val_EditSend);
	DDX_Control(pDX, IDC_EditShow, m_Ctrl_EditShow);
	DDX_Control(pDX, IDC_BntConnect, m_Ctrl_BntConnect);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BntConnect, &CMFCClientDlg::OnBnClickedBntconnect)
	ON_BN_CLICKED(IDC_BntSend, &CMFCClientDlg::OnBnClickedBntsend)
END_MESSAGE_MAP()


// CMFCClientDlg 消息处理程序

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCClientDlg::OnPaint()
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
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 收数处理函数
bool CMFCClientDlg::ReceiveData(CClient * pServer)
{
	// TODO: 在此处添加实现代码.
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char) * 1024);
	UCHAR leng = 0;
	CString str;
	leng = m_Client->Receive(pData, 1024, 0);
	str = pData;
	if (!UpdateEditShow(_T("接收：") + str))	AfxMessageBox(_T("显示编辑框更新失败！"));
	delete pData;
	pData = NULL;
	return false;
}


// 发送函数
bool CMFCClientDlg::SendMsg()
{
	// TODO: 在此处添加实现代码.
	UpdateData(TRUE);
	char *pSend = new char[m_Val_EditSend.GetLength()];
	memset(pSend, 0, m_Val_EditSend.GetLength() * sizeof(char));
	if (!(m_Client->WChar2MByte(m_Val_EditSend.GetBuffer(0), pSend, m_Val_EditSend.GetLength())))
	{
		AfxMessageBox(_T("字符转换失败"));
		delete pSend;
		return false;
	}
	if (m_Client == NULL)	return false;
	if (m_Client->Send(pSend, m_Val_EditSend.GetLength()) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送失败"));
		return false;
	}
	return true;
}


// 更新显示编辑框
int CMFCClientDlg::UpdateEditShow(CString s)
{
	// TODO: 在此处添加实现代码.
	UpdateData(TRUE);
	CString str_tem, str;
	m_Ctrl_EditShow.GetWindowTextW(str_tem);
	CTime time = CTime::GetCurrentTime();
	str = time.Format(_T("%Y-%m-%d %H:%M:%S  ")) + _T("\r\n") + s;
	str = str_tem + str + _T("\r\n\r\n");
	m_Ctrl_EditShow.SetWindowTextW(str);
	int lineCount = m_Ctrl_EditShow.GetLineCount();
	m_Ctrl_EditShow.LineScroll(lineCount);
	return 1;
}


void CMFCClientDlg::OnBnClickedBntconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_flg_Connect)                             // 如果已经连接，则断开服务器
	{
		m_flg_Connect = false;
		m_Client->Close();
		delete m_Client;
		m_Client = NULL;
		m_Ctrl_BntConnect.SetWindowTextW(_T("连接服务器"));
		UpdateData(false);
		return;
	}
	else
	{
		// 未连接，则连接服务器
		UpdateData(TRUE);
		m_Client = new CClient();
		m_Client->m_ClientDlg = this;
		if (!m_Client->Create())         //创建套接字
		{
			AfxMessageBox(_T("创建套接字失败！"));
			return;
		}
		
		if (!m_Client->Connect(m_Val_EditIp, m_Val_EditPort))    //连接服务器
		{
			AfxMessageBox(_T("连接服务器失败！"));
			return;
		}
		else
		{
			m_flg_Connect = true;
			m_Ctrl_BntConnect.SetWindowTextW(_T("断开服务器"));
			UpdateData(false);

		}
	}
}


void CMFCClientDlg::OnBnClickedBntsend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_flg_Connect)
	{
		if (!SendMsg())
		{
			AfxMessageBox(_T("发送失败，请确认服务器状态"));
			return;
		}
		UpdateData(TRUE);
		UpdateEditShow(_T("发送：") + m_Val_EditSend);
	}
	else
	{
		AfxMessageBox(_T("请先连接服务器"));
	}
	
}
