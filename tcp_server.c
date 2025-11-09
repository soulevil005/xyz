#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error in socket.\n");
        exit(1);
    }
    printf("TCP Server Socket created.\n");

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error in bind.\n");
        exit(1);
    }
    printf("Bind successful.\n");

    if (listen(sockfd, 5) == 0)
        printf("Listening...\n");
    else {
        printf("Error in listening.\n");
        exit(1);
    }

    addr_size = sizeof(clientAddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &addr_size);

    recv(newsockfd, buffer, 1024, 0);
    printf("Client: %s\n", buffer);

    strcpy(buffer, "Hello from Server!");
    send(newsockfd, buffer, strlen(buffer), 0);

    close(newsockfd);
    close(sockfd);

    return 0;
}
