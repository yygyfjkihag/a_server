/*
 * server.cpp
 *
 *  Created on: 2017��3��10��
 *      Author: yygyfjkihag
 */
#include <iostream>
#include "A_server.h"
using namespace std;

int main(){
	A_server svr;
	svr.initListen(8700);
	while(true){
		if(svr.isReady()){
			while(true){
				svr.exch_Msg();
			}
		}
		else{
			cout<<"accept error: "<<WSAGetLastError()<<endl;
		}
	}

	WSACleanup();
	return 0;
}


