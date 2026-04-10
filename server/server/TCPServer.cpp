#include "pch.h"
#include "TCPServer.h"

void TCPServer::setup(int port)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);
	bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(sockfd, 5);
}

string TCPServer::receive()
{
	while (true)
	{
		socklen_t sosize = sizeof(clientAddress);
		int clientSock = accept(sockfd, (struct sockaddr*)&clientAddress, &sosize);

		if (clientSock < 0)
		{
			cout << "Accept error" << endl;
			continue;
		}

		thread(Task, clientSock).detach();
	}
	return "";
}

void TCPServer::Send(int clientSock, string msg)
{
	send(clientSock, msg.c_str(), msg.length(), 0);
}

void TCPServer::Task(int clientSock)
{
	char msg[MAX_PACKET_SIZE];
	while (true)
	{
		int n = recv(clientSock, msg, MAX_PACKET_SIZE, 0);
		if (n <= 0) 
		{
			closesocket(clientSock);
			break;
		}
		msg[n] = '\0';
		string received(msg);
		char ch = 'a' + rand() % 26;
		std::string response = " [client message: " + received + "] ";
		response += ch;

		send(clientSock, response.c_str(), response.length(), 0);
	}
}

void TCPServer::detach()
{
	closesocket(sockfd);
}
