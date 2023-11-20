#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Connect to localhost

    // Send data to the server
    const char* message = "Hello from client!";
    sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Receive a response from the server
    char buffer[1024];
    socklen_t serverAddressLength = sizeof(serverAddress);
    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddress, &serverAddressLength);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return 1;
    }

    std::cout << "Received from server: " << buffer << std::endl;

    // Close the socket
    close(clientSocket);

    return 0;
}
