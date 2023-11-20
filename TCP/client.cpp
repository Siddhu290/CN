#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Connect to localhost

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Send data to the server
    const char* message = "Hello from client!";
    send(clientSocket, message, strlen(message), 0);

    // Receive a response from the server
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data" << std::endl;
        return 1;
    }

    std::cout << "Received from server: " << buffer << std::endl;

    // Close the socket
    close(clientSocket);

    return 0;
}
