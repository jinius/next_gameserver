#include "stdafx.h"
#include "EchoServer.h"

EchoServer::EchoServer()
{
}


EchoServer::~EchoServer()
{
}


bool EchoServer::InitServer( HWND hWnd )
{
	m_hWnd = hWnd;

	return true;
}


bool EchoServer::StartServer( int port )
{
	WSADATA			wsaData;

	if ( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		return false;

	m_ListenSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if ( m_ListenSocket == INVALID_SOCKET )
		return false;

	int opt = 1;
	setsockopt( m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof( int ) );

	if ( SOCKET_ERROR == WSAAsyncSelect( m_ListenSocket, m_hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE ) )
		return false;

	SOCKADDR_IN serveraddr;
	ZeroMemory( &serveraddr, sizeof( serveraddr ) );
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons( port );
	serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );
	int ret = bind( m_ListenSocket, (SOCKADDR*)&serveraddr, sizeof( serveraddr ) );
	if ( ret == SOCKET_ERROR )
		return false;

	ret = listen( m_ListenSocket, SOMAXCONN );
	if ( ret == SOCKET_ERROR )
		return false;

	return true;
}


bool EchoServer::Shutdown()
{
	return true;
}
