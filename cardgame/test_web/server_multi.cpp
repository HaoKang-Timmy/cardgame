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
            //接受远程来连接
            this_thread::sleep_for(chrono::milliseconds(100));
            int remoteSock = w.acceptSock();
            if(remoteSock==-1)
                continue;
            if(remoteSock != INVALID_SOCKET){
                lock_guard<std::mutex> mtx_locker(mtx);
                remote.emplace_back(remoteSock);
                cout<<"成功加入一个client:"<<remoteSock<<endl;
                //Respond(remoteSock);
            }
        }
    }, w);

    thread recvThread([](winSock w){
        constexpr int maxSize = 100;
        char send_buf[maxSize];
        int recvBytes;
        while(true){
            //0.3s检测一次,一定要有不然cpu占用会很大的
            this_thread::sleep_for(chrono::milliseconds(300));
            lock_guard<std::mutex> mtx_locker(mtx);
            for(auto iter = remote.begin();iter != remote.end();){
            	struct Message m = w.Recv(*iter);
                recvBytes = m.recvByte;
                if(recvBytes == 0){
                    iter = remote.erase(iter);
                    cout<<"客户端:"<<*iter<<"连接错误成功移除"<<endl;
                    continue;
                } else if(recvBytes<0){
                    ++iter;
                }
                else{
                    cout<< "从客户端接收到信息:" << m.recv_buf << " from sock : " << *iter << endl;
                    cout << "请输入回复信息:";
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
