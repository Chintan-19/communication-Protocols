#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int sock, n;
    char buffer[1024];
    struct sockaddr_in serv_addr;

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize socket structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (true) {
        // Clear buffer
        memset(buffer, 0, sizeof(buffer));

        // Get message from user
        cout << "Enter message: ";
        cin.getline(buffer, sizeof(buffer));

        // Send message to server
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

        // Receive message from server
        n = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[n] = '\0';

        // Print message received from server
        cout << "Message received: " << buffer << endl;
    }

    // Close socket
    close(sock);

    return 0;
}
