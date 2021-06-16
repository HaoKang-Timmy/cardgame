#ifndef _WINSOCK_
#define _WINSOCK_

#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

//! information of recv from client
struct Message {
	int recvByte;
	char recv_buf[100];
};

/**
 * @brief class for windows socket
 * 
 */
class winSock {

private:
	
	//! server socket
	SOCKET s_server;
	//! receiver socket
	SOCKET s_accept;
	//! addr of server
	SOCKADDR_IN server_addr;
	//! addr of receiver
	SOCKADDR_IN accept_addr;
	
public:
	
	//! WinSock Constructor
	winSock(); 
	
	/**
	 * @brief Set the Server Information
	 * 
	 * @param [in] host - port number 
	 */
	void setServerInf(int host);
	
	/**
	 * @brief bind the socket
	 * 
	 */
	void bindSock();

	/**
	 * @brief set socket to listening
	 * 
	 */
	void listenSock();

	/**
	 * @brief connect to server
	 * 
	 */
	void connectSock();
	
	/**
	 * @brief waiting the client to connect
	 * 
	 * @return connect status
	 */
	int acceptSock(); 

	/**
	 * @brief receive message from others
	 * 
	 * @return receive Message 
	 */
	struct Message Recv();
	
	/**
	 * @brief receive message from others
	 * 
	 * @param [in] sock - client number 
	 * @return Message 
	 */
	struct Message Recv(int sock);

	/**
	 * @brief send message to others
	 * 
	 * @param [in] message - the message send to others 
	 * @return send status 
	 */
	int Send(char message[]);

	/**
	 * @brief send message to others
	 * 
	 * @param [in] message - the message send to others 
	 * @return send status 
	 */
	int Send(int sock, char message[]);

	/**
	 * @brief close socket
	 * 
	 */
	void closeSock();
}; 

#endif
