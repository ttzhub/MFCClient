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
	// TODO: �ڴ����ר�ô����/����û���


	CSocket::OnConnect(nErrorCode);
}


void CClient::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnSend(nErrorCode);
}


void CClient::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_ClientDlg->ReceiveData(this);

	CSocket::OnReceive(nErrorCode);
}


bool CClient::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n < nlen)	return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
	
}
