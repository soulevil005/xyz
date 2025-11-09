#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Error in socket.\n");
        exit(1);
    }
    printf("UDP Server Socket created.\n");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error in bind.\n");
        exit(1);
    }
    printf("Bind successful. Waiting for client...\n");

    addr_size = sizeof(clientAddr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &addr_size);
    printf("Client: %s\n", buffer);

    strcpy(buffer, "Hello from UDP Server!");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&clientAddr, addr_size);

    close(sockfd);
    return 0;
}
