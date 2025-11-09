#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error in socket.\n");
        exit(1);
    }
    printf("TCP Client Socket created.\n");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Connected to Server.\n");

    strcpy(buffer, "Hello from Client!");
    send(sockfd, buffer, strlen(buffer), 0);

    recv(sockfd, buffer, 1024, 0);
    printf("Server: %s\n", buffer);

    close(sockfd);

    return 0;
}
