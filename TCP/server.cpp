#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Accept an incoming connection
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        return 1;
    }

    // Receive data from the client
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return 1;
    }

    std::cout << "Received from client: " << buffer << std::endl;

    // Send a response back to the client
    const char* response = "Hello from server!";
    send(clientSocket, response, strlen(response), 0);

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
