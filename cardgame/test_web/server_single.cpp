#include "winsock.h"
#include "winsock.cpp"
using namespace std;
void initialization();
int main() {
	//���巢�ͻ�����
	char send_buf[100];
	//������������׽���
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
			cout << "���ӽ�����׼����������" << endl;
			break;
		}
	}
	//��������
	while (1) {
		struct Message m;
		m = w.Recv(s_accept);
		if (m.recvByte < 0)
			continue;
		else
			cout << "�ͻ�����Ϣ:" << m.recv_buf << endl;
		cout << "������ظ���Ϣ:";
		cin >> send_buf;
		w.Send(s_accept, send_buf);
	}
	
	w.closeSock();
	return 0;
}
