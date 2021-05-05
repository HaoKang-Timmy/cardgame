#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include "winSock.h"
#include "winSock.cpp"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

vector<int> remote;
mutex mtx;


int main(){
	std::cout << "hello server ... " << std::endl;
    winSock w; 
	w.setServerInf(8888);
	w.bindSock();
	w.listenSock();
    /*thread listenThread(Listen, listenSock);*/
    thread listenThread([](winSock w){
        sockaddr_in remoteAddr{};
        int size = sizeof(remoteAddr);
        while(true){
            //����Զ��������
            this_thread::sleep_for(chrono::milliseconds(100));
            int remoteSock = w.acceptSock();
            if(remoteSock==-1)
                continue;
            if(remoteSock != INVALID_SOCKET){
                lock_guard<std::mutex> mtx_locker(mtx);
                remote.emplace_back(remoteSock);
                cout<<"�ɹ�����һ��client:"<<remoteSock<<endl;
                //Respond(remoteSock);
            }
        }
    }, w);

    thread recvThread([](winSock w){
        constexpr int maxSize = 100;
        char send_buf[maxSize];
        int recvBytes;
        while(true){
            //0.3s���һ��,һ��Ҫ�в�Ȼcpuռ�û�ܴ��
            this_thread::sleep_for(chrono::milliseconds(300));
            lock_guard<std::mutex> mtx_locker(mtx);
            for(auto iter = remote.begin();iter != remote.end();){
            	struct Message m = w.Recv(*iter);
                recvBytes = m.recvByte;
                if(recvBytes == 0){
                    iter = remote.erase(iter);
                    cout<<"�ͻ���:"<<*iter<<"���Ӵ���ɹ��Ƴ�"<<endl;
                    continue;
                } else if(recvBytes<0){
                    ++iter;
                }
                else{
                    cout<< "�ӿͻ��˽��յ���Ϣ:" << m.recv_buf << " from sock : " << *iter << endl;
                    cout << "������ظ���Ϣ:";
					cin >> send_buf;
					w.Send(*iter, send_buf);
                    ++iter;
                }
            }
        }
    }, w);

    listenThread.join();
    recvThread.join();

    w.closeSock();
    return 0;
}
