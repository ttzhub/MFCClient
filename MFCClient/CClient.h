#pragma once
#include "MFCClientDlg.h"

class CMFCClientDlg;

class CClient : public CSocket
{
public:
	CClient();
	~CClient();
	// ClientDlg´°¿Ú
	CMFCClientDlg * m_ClientDlg;
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	bool WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);
};

