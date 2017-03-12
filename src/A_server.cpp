/*
 * A_server.cpp
 *
 *  Created on: 2017Äê3ÔÂ10ÈÕ
 *      Author: yygyfjkihag
 */

#include "A_server.h"

A_server::A_server(){
	socketBoost();
	sock=socket(AF_INET, SOCK_STREAM, 0);
	sock_con=socket(AF_INET, SOCK_STREAM, 0);
}

bool A_server::socketBoost() {
	WORD wVerReq = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err;

	err = WSAStartup(wVerReq, &wsaData);
	if (0 != err) {
		cout << "Server-WSAStartup failed. Return:" << err << endl;
		return false;
	}

	if (wsaData.wVersion != wVerReq) {
		cout << "Server-wsaData.wVersion: " << wsaData.wVersion
				<< " is not equal to wVerReq: " << wVerReq << endl;
		WSACleanup();
		return false;
	}
	return true;
}

/********************************************************
 *
 *
 *
 *
 ********************************************************/
bool A_server::initListen(const unsigned short serverPort) {
	int err;
	SOCKADDR_IN addr_server;

	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(serverPort);
	addr_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	err = bind(sock, (SOCKADDR*) &addr_server, sizeof(addr_server));
	if (SOCKET_ERROR == err) {
		cout << "Server-bind error:" << WSAGetLastError() << endl;
		return false;
	}

	err = listen(sock, 2);
	if ( SOCKET_ERROR == err) {
		cout << "Server-listen error: " << WSAGetLastError() << endl;
		return false;
	}

	//cout << inet_ntoa(addr_server.sin_addr)<<endl;
	cout << "Start listening on port: " << serverPort << endl;
	return true;
}

bool A_server::initListen(const char* serverIp,const unsigned short serverPort) {
	int err;
	SOCKADDR_IN addr_server;

	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(serverPort);
	addr_server.sin_addr.S_un.S_addr = inet_addr(serverIp);

	err = bind(sock, (SOCKADDR*) &addr_server, sizeof(addr_server));
	if (SOCKET_ERROR == err) {
		cout << "Server-bind error:" << WSAGetLastError() << endl;
		return false;
	}

	err = listen(sock, 2);
	if ( SOCKET_ERROR == err) {
		cout << "Server-listen error: " << WSAGetLastError() << endl;
		return false;
	}
	cout << "Listening locatehost("<<serverIp<<") on port: " << serverPort << endl;
	return true;
}

/********************************************************
 *
 *
 *
 *
 ********************************************************/
bool A_server::isReady() {
	SOCKADDR_IN addr_client;
	int addrlen;

	addrlen = sizeof(addr_client);
	sock_con = accept(sock, (SOCKADDR*) &addr_client, &addrlen);
	if (INVALID_SOCKET != sock_con) {
		cout << inet_ntoa(addr_client.sin_addr) << ":"
			 << ntohs(addr_client.sin_port) << " is connected successfully!" << endl;
		return true;
	} else{
		cout<<"**** CONNECT UNSUCCESSFULLY!"<<endl;
		return false;
	}
}

bool A_server::exchange_Msg() {
	int err;

	err = recv(sock_con, recv_buf, sizeof(recv_buf), 0);
	if (err <= 0) {
		cout << "Server-recv error or client leaves: "<< WSAGetLastError() << endl;
		return false;
	}

	sprintf(send_buf, "Server receive msg: %s", recv_buf);

	err = send(sock_con, send_buf, strlen(send_buf) + 1, 0);
	if ( SOCKET_ERROR == err) {
		cout << "Server-send error or client leaves: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

void A_server::close() {
	int err;

	err = closesocket(sock_con);
	if ( SOCKET_ERROR == err) {
		cout << "Server-closeSock error: " << WSAGetLastError() << endl;
	}
	err = closesocket(sock);
	if ( SOCKET_ERROR == err) {
		cout << "Server-closeSock_con error: " << WSAGetLastError() << endl;
	}
	WSACleanup();
}


