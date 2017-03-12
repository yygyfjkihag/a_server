/*
 * server.cpp
 *
 *  Created on: 2017Äê3ÔÂ10ÈÕ
 *      Author: yygyfjkihag
 */
#include <iostream>
#include "A_server.h"
using namespace std;

const char* serverIp = "127.0.0.1";
const unsigned short serverPort = 8700;
int main(){
	A_server svr;
	//svr.initListen(serverIp,serverPort);
	svr.initListen(serverPort);

	while(true){
		if(svr.isReady()){
			while(svr.exchange_Msg());
		}
	}
}


