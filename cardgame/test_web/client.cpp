
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#include "winSock.h"
#include "winSock.cpp"
using namespace std;
void initialization();
int main() {

	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[100];

	winSock w;
	w.setServerInf(8888);
	w.connectSock();
 
	//����,��������
	while (1) {
		cout << "�����뷢����Ϣ:";
		cin >> send_buf;
		send_len = w.Send(send_buf);
		if (send_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		struct Message m;
		m = w.Recv();
		recv_len = m.recvByte;
		if (recv_len < 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else {
			cout << "�������Ϣ:" << m.recv_buf << endl;
		}
	}
	
	w.closeSock();
	
	return 0;
}
