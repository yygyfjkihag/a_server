/*
 * server.cpp
 *
 *  Created on: 2017Äê3ÔÂ10ÈÕ
 *      Author: yygyfjkihag
 */
#include <iostream>
#include "A_server.h"
using namespace std;
const unsigned short serverPort = 8700;
int main(){
	A_server svr;
	svr.initListen(serverPort);
	while(true){
		if(svr.isReady()){
			while(1==svr.exch_Msg());
		}
		else{
			cout<<"accept error: "<<WSAGetLastError()<<endl;
		}
	}

	WSACleanup();
	return 0;
}


