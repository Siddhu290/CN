#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    char buffer[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Open a file to save received data
    std::ofstream file("received_file.txt", std::ios::binary);

    // Receive and write file data
    int bytes_received;
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytes_received);
    }

    std::cout << "File received and saved as received_file.txt" << std::endl;

    // Close socket and file
    close(client_socket);
    file.close();

    return 0;
}
