#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    if (argv[1] == 0)
    {
        printf("No address was entered\n");
        return 1;
    }

    char *address;
    int port;
    address = argv[1];
    if (argv[2] == 0)
    {
        port = 80;
    }
    else
    {
        port = atoi(argv[2]);
    }

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to address
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(port);
    remote_address.sin_addr.s_addr = inet_addr(address);

    connect(client_socket, (struct sockaddr *)&remote_address, sizeof(remote_address));

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, &response, sizeof(response), 0);

    printf("Response from the server:\n%s\n", response);

    closesocket(client_socket);
    WSACleanup();

    return 0;
}