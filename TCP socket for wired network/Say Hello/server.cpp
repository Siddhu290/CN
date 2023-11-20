#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_addr_len = sizeof(client_address);

    char message[] = "Hello from server!";
    char buffer[1024];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 5);
    std::cout << "Server listening on port 12345..." << std::endl;

    // Accept client connection
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_addr_len);

    // Send a hello message to the client
    send(client_socket, message, strlen(message), 0);

    // Receive message from the client
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl;

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
