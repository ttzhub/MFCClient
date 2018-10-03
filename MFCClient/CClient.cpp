#include "stdafx.h"
#include "CClient.h"


CClient::CClient()
{
}


CClient::~CClient()
{
}


void CClient::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类


	CSocket::OnConnect(nErrorCode);
}


void CClient::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnSend(nErrorCode);
}


void CClient::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_ClientDlg->ReceiveData(this);

	CSocket::OnReceive(nErrorCode);
}


bool CClient::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	// TODO: 在此处添加实现代码.
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n < nlen)	return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
	
}
