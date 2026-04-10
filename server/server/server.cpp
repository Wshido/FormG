#include "pch.h"
#include "TCPServer.h"

TCPServer tcp;

int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "WSAStartup failed" << endl;
        return 1;
    }
    srand(time(NULL));
    tcp.setup(11999);
    tcp.receive();
    WSACleanup();
    return 0;
}
