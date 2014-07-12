#pragma once

#include <WinSock2.h>
#include <thread>

#define WM_SOCKET (WM_USER + 1)

class EchoServer
{
public:
	EchoServer();
	~EchoServer();

	bool InitServer( HWND hWnd );
	bool StartServer( int port );
	bool Shutdown();

private:
	HWND			m_hWnd;
	SOCKET			m_ListenSocket;
};

