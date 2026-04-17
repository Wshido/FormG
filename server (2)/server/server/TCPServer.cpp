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

        stringstream ss(msg);

        double a, b, c, start, end, step;
        ss >> a >> b >> c >> step;

        string response;

        for (double x = -10; x <= 10; x += step)
        {
            double y;

            if (x < 0)
            {
                y = sin(a * x);
            }
            else if (x < 1)
            {
                if (b * x < 0)
                {
                    response += "x=" + to_string(x) + " y=NaN\n";
                    continue;
                }
                y = sqrt(b * x);
            }
            else
            {
                if (c * x - 1 == 0)
                {
                    response += "x=" + to_string(x) + " y=INF\n";
                    continue;
                }
                y = 1.0 / (c * x - 1);
            }

            response += "x=" + to_string(x) +
                " y=" + to_string(y) + "\n";
        }

        send(clientSock, response.c_str(), response.length(), 0);
    }
}

void TCPServer::detach()
{
	closesocket(sockfd);
}
