/*
 * A_server.cpp
 *
 *  Created on: 2017Äê3ÔÂ10ÈÕ
 *      Author: yygyfjkihag
 */

#include "A_server.h"

A_server::A_server() {
	init();
	sock=socket(AF_INET, SOCK_STREAM, 0);
	sock_con=socket(AF_INET, SOCK_STREAM, 0);

	/**
	 * test port
	 */
	if(INVALID_SOCKET == sock||INVALID_SOCKET == sock_con)
	cout<<"server--sock/con create error. "<<endl;

}

int A_server::init() {
	WORD wVerReq = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err = WSAStartup(wVerReq, &wsaData);
	if (0 != err) {
		cout << "Server-WSAStartup failed. Return:" << err << endl;
		return -1;
	}

	if (wsaData.wVersion != wVerReq) {
		cout << "Server-wsaData.wVersion: " << wsaData.wVersion
				<< " is not equal to wVerReq: " << wVerReq << endl;
		WSACleanup();
		return -2;
	}
	return 1;
}

int A_server::initListen(const unsigned short serverPort) {
	int err;

	if (INVALID_SOCKET == sock) {
		cout << "Server-socket error:" << WSAGetLastError() << endl;
		return -3;
	}

	SOCKADDR_IN addr_server;
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(serverPort);
	addr_server.sin_addr.S_un.S_addr = htonl(0);

	err = bind(sock, (SOCKADDR*) &addr_server, sizeof(addr_server));
	if (SOCKET_ERROR == err) {
		cout << "Server-bind error:" << WSAGetLastError() << endl;
		return -4;
	}

	err = listen(sock, 2);
	if ( SOCKET_ERROR == err) {
		cout << "Server-listen error: " << WSAGetLastError() << endl;
		return -5;
	}

	cout << "Start listening on port: " << serverPort << endl;
	return 1;
}

bool A_server::isReady() {
	int addrlen = sizeof(addr_client);
	sock_con = accept(sock, (SOCKADDR*) &addr_client, &addrlen);
	if (INVALID_SOCKET != sock_con) {
		cout << inet_ntoa(addr_client.sin_addr) << ":"
				<< ntohs(addr_client.sin_port) << " connected!" << endl;
		return 1;
	} else
		return 0;
}

int A_server::exch_Msg() {
	int err;

	err = recv(sock_con, recv_buf, sizeof(recv_buf), 0);

	if (err <= 0) {
		cout << "Server-recv error: " << WSAGetLastError() << endl;
		return -1;
	}

	sprintf(send_buf, "Server receive msg: %s", recv_buf);

	err = send(sock_con, send_buf, strlen(send_buf) + 1, 0);

	if ( SOCKET_ERROR == err) {
		cout << "Server-send error: " << WSAGetLastError() << endl;
		return -2;
	}
	return 1;
}

void A_server::close() {
	int err = closesocket(sock_con);
	if ( SOCKET_ERROR == err) {
		cout << "Server-closeSocket error: " << WSAGetLastError() << endl;
	}
}
