
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#include "winSock.h"
#include "winSock.cpp"
using namespace std;
void initialization();
int main() {

	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100];

	winSock w;
	w.setServerInf(8888);
	w.connectSock();
 
	//发送,接收数据
	while (1) {
		cout << "请输入发送信息:";
		cin >> send_buf;
		send_len = w.Send(send_buf);
		if (send_len < 0) {
			cout << "发送失败！" << endl;
			break;
		}
		struct Message m;
		m = w.Recv();
		recv_len = m.recvByte;
		if (recv_len < 0) {
			cout << "接受失败！" << endl;
			break;
		}
		else {
			cout << "服务端信息:" << m.recv_buf << endl;
		}
	}
	
	w.closeSock();
	
	return 0;
}
