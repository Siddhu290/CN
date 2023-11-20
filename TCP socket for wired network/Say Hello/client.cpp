#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    char message[] = "Hello from client!";
    char buffer[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Send a hello message to the server
    send(client_socket, message, strlen(message), 0);

    // Receive message from the server
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Message from server: " << buffer << std::endl;

    // Close socket
    close(client_socket);

    return 0;
}
