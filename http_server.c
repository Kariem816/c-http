#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/types.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    // open a file to serve
    FILE *html;
    html = fopen("index.html", "r");

    char response_data[1024];
    
    fgets(response_data, 1024, html);

    fclose(html);

    char http_header[2048] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    strcat(http_header, response_data);

    // create a socket
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    int server_addrlen = sizeof(server_address);

    server_address.sin_family = AF_INET;                // IPv4
    server_address.sin_port = htons(8080);              // htons = host to network short, port
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY => "0.0.0.0"

    // bind the socket to a specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, server_addrlen);

    listen(server_socket, SOMAXCONN); // args => (socket, number of waiting connections at one time)
    printf("server listening on port: 8080\n\n");

    while (1)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&server_addrlen); // args => (socket you accept connections on, address of client, type of connection)
        // send the data
        send(client_socket, http_header, sizeof(http_header), 0); // args => (where to, message, size of the message, flags?)
        // close the socket
        closesocket(client_socket);
    }

    return 0;
}