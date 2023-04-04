#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
    int sock, n;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len = sizeof(cli_addr);

    // Create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize socket structure
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8888);

    // Bind the socket with the server address
    bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    while (true) {
        // Receive message from client
        n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &cli_addr, &len);
        buffer[n] = '\0';

        // Print message received from client
        cout << "Message received: " << buffer << endl;

        // Send message to client
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &cli_addr, len);

        // Clear buffer
        memset(buffer, 0, sizeof(buffer));
    }

    // Close socket
    close(sock);

    return 0;
}
