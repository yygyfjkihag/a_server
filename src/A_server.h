/*
 * A_server.h
 *
 *  Created on: 2017Äê3ÔÂ10ÈÕ
 *      Author: yygyfjkihag
 */

#ifndef A_SERVER_H_
#define A_SERVER_H_

#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <string.h>
using namespace std;

class A_server {
private:
	char recv_buf[256];
	char send_buf[512];
	SOCKET sock;
	SOCKET sock_con;
	SOCKADDR_IN addr_client;

public:
	A_server();
	int init();
	int initListen(const unsigned short serverPort);
	bool isReady();
	void exch_Msg();
	void close();
	virtual ~A_server(){};
};

#endif /* A_SERVER_H_ */
