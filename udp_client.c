#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Error in socket.\n");
        exit(1);
    }
    printf("UDP Client Socket created.\n");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    strcpy(buffer, "Hello from UDP Client!");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    addr_size = sizeof(serverAddr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, &addr_size);
    printf("Server: %s\n", buffer);

    close(sockfd);
    return 0;
}
