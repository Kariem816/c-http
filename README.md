# C HTTP Server/Client

This is a very basic HTTP server and client written in C. I made it with the help of documentation and tutorials on the internet. I made this to learn more about how HTTP works and how to make a server and client in C.

## How to use

### Server

1. Compile the server.c file with `gcc http_server.c -o server -lws2_32`

2. Run the server with `./server`

3. The server will now be running on localhost port 8080

4. The server will serve the `index.html` file on every endpoint and method

### Client

1. Compile the client.c file with `gcc http_client.c -o client -lws2_32`

2. Run the client with `./client <ip> <port>`

3. The response from the server will be printed to the console
> Note: The client can send to any ip and port (not neccecarily the server), but the server will only respond to the ip and port it is running on.