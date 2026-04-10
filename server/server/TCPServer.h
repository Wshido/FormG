#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include "pch.h"

class TCPServer
{
public:
	int sockfd;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	void setup(int port);
	string receive();
	void Send(int clientSock, string msg);
	void detach();

private:
	static void Task(int clientSock);
};
#endif