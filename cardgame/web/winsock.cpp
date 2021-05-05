#include "winsock.h"

using namespace std;

winSock::winSock() 
{
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) 
		cout << "初始化套接字库失败！" << endl;
	else 
		cout << "初始化套接字库成功！" << endl;
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else 
		cout << "套接字库版本正确！" << endl;
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
}
	
void winSock::setServerInf(int host) 
{
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(host);
}
	
void winSock::bindSock() 
{
	// 套接字绑定 
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
	}
	else 
		cout << "套接字绑定成功！" << endl;
}
	
	/* 阻塞 
	void listenSock() {
		//把 监听套接字 设置为非阻塞, 这样recv()和accept()就为非阻塞了
    //	unsigned long ulMode = 1;
    //	ioctlsocket(s_server, FIONBIO, &ulMode);
		//设置套接字为监听状态
		if (listen(s_server, SOMAXCONN) < 0) {
			cout << "设置监听状态失败！" << endl;
			WSACleanup();
		}
		else {
			cout << "设置监听状态成功！" << endl;
		}
	} 
	
	int acceptSock() {
		int len = sizeof(SOCKADDR);
		cout<<s_server<<endl;
		s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
		if (s_accept == SOCKET_ERROR) {
			cout << "连接失败！" << endl;
			WSACleanup();
			return 0;
		}
		cout << "连接建立，准备接受数据" << endl;
		return s_accept;
	}*/ 
	
	// 非阻塞 
void winSock::listenSock()
{
	//把 监听套接字 设置为非阻塞, 这样recv()和accept()就为非阻塞了
    unsigned long ulMode = 1;
   	ioctlsocket(s_server, FIONBIO, &ulMode);
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
	}
	else 
		cout << "设置监听状态成功！" << endl;
} 

void winSock::connectSock()
{
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		WSACleanup();
	}
	else {
		cout << "服务器连接成功！" << endl;
	}
}
	
int winSock::acceptSock() 
{
	int len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
	return s_accept;
}
	
struct Message winSock::Recv() 
{
	struct Message m;
	m.recvByte = recv(s_server, m.recv_buf, 100, 0);
	return m;
}
	
struct Message winSock::Recv(int sock) 
{
	struct Message m;
	m.recvByte = recv(sock, m.recv_buf, 100, 0);
	return m;
}

int winSock::Send(char message[])
{
	return send(s_server, message, 100, 0);
}	
	
int winSock::Send(int sock, char message[])
{
	return send(sock, message, 100, 0);
}	
	
void winSock::closeSock()
{
	//释放服务器资源
   	closesocket(s_server);
	closesocket(s_accept);
  	//释放资源
  	WSACleanup();
} 

