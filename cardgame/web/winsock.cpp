#include "winsock.h"

using namespace std;

winSock::winSock() 
{
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) 
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	else 
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else 
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
}
	
void winSock::setServerInf(int host) 
{
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(host);
}
	
void winSock::bindSock() 
{
	// �׽��ְ� 
	if (bind(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else 
		cout << "�׽��ְ󶨳ɹ���" << endl;
}
	
	/* ���� 
	void listenSock() {
		//�� �����׽��� ����Ϊ������, ����recv()��accept()��Ϊ��������
    //	unsigned long ulMode = 1;
    //	ioctlsocket(s_server, FIONBIO, &ulMode);
		//�����׽���Ϊ����״̬
		if (listen(s_server, SOMAXCONN) < 0) {
			cout << "���ü���״̬ʧ�ܣ�" << endl;
			WSACleanup();
		}
		else {
			cout << "���ü���״̬�ɹ���" << endl;
		}
	} 
	
	int acceptSock() {
		int len = sizeof(SOCKADDR);
		cout<<s_server<<endl;
		s_accept = accept(s_server, (SOCKADDR *)&accept_addr, &len);
		if (s_accept == SOCKET_ERROR) {
			cout << "����ʧ�ܣ�" << endl;
			WSACleanup();
			return 0;
		}
		cout << "���ӽ�����׼����������" << endl;
		return s_accept;
	}*/ 
	
	// ������ 
void winSock::listenSock()
{
	//�� �����׽��� ����Ϊ������, ����recv()��accept()��Ϊ��������
    unsigned long ulMode = 1;
   	ioctlsocket(s_server, FIONBIO, &ulMode);
	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0) {
		cout << "���ü���״̬ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else 
		cout << "���ü���״̬�ɹ���" << endl;
} 

void winSock::connectSock()
{
	if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "����������ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else {
		cout << "���������ӳɹ���" << endl;
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
	//�ͷŷ�������Դ
   	closesocket(s_server);
	closesocket(s_accept);
  	//�ͷ���Դ
  	WSACleanup();
} 

