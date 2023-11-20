#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to an IP address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Receive data from the client
    char buffer[1024];
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return 1;
    }

    std::cout << "Received from client: " << buffer << std::endl;

    // Send a response back to the client
    const char* response = "Hello from server!";
    sendto(serverSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddress, clientAddressLength);

    // Close the socket
    close(serverSocket);

    return 0;
}
