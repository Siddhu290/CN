#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>  // Add this line for close function
#include <netinet/in.h>  // Add this line for struct sockaddr_in

// Function to send a file over UDP
void sendFile(const char* filename, const char* destination_ip, int port) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, destination_ip, &server_addr.sin_addr);

    char buffer[1024];
    ssize_t bytesRead;

    while (true) {
        file.read(buffer, sizeof(buffer));
        bytesRead = file.gcount();
        if (bytesRead <= 0) {
            break;  // End of file
        }

        sendto(sockfd, buffer, bytesRead, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    file.close();
    close(sockfd);
    std::cout << "File " << filename << " sent successfully." << std::endl;
}

int main() {
    const char* serverIP = "destination_machine_ip"; // Replace with the destination machine's IP
    int port = 12345;  // Replace with your chosen port number

    // Send script, text, audio, and video files
    sendFile("script.txt", serverIP, port);
    sendFile("text.txt", serverIP, port);
    sendFile("audio.mp3", serverIP, port);
    sendFile("video.mp4", serverIP, port);

    return 0;
}
