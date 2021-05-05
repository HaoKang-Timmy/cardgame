#include "winsock.h"
#include "winsock.cpp"
using namespace std;
void initialization();
int main() {
	//定义发送缓冲区
	char send_buf[100];
	//定义接受请求套接字
	SOCKET s_accept;
	winSock w;
	w.setServerInf(8888);
	w.bindSock();
	w.listenSock();
	while(1) {
		s_accept = w.acceptSock();
		if (s_accept == SOCKET_ERROR)
			continue;
		else if(s_accept != INVALID_SOCKET) {
			cout << "连接建立，准备接受数据" << endl;
			break;
		}
	}
	//接收数据
	while (1) {
		struct Message m;
		m = w.Recv(s_accept);
		if (m.recvByte < 0)
			continue;
		else
			cout << "客户端信息:" << m.recv_buf << endl;
		cout << "请输入回复信息:";
		cin >> send_buf;
		w.Send(s_accept, send_buf);
	}
	
	w.closeSock();
	return 0;
}
