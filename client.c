#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if (argc < 3)
    {
        fprintf(stderr, "Usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Error connection");
    printf("Client: ");
    // while(1)
    // {
    //     bzero(buffer, 255);
    //     fgets(buffer, 255, stdin);
    //     n = write(sockfd, buffer, strlen(buffer));
    //     if (n < 0)
    //         error("Error writing to socket");
    //     bzero(buffer, 255);
    //     n = read(sockfd, buffer, 255);
    //     if(n < 0)
    //         error("Error reading from socket");
    //     printf("Server : %s\n", buffer);
    //     int i = strncmp("Bye", buffer, 3);
    //     if (i == 0)
    //         break;
    // }
    int num1, num2, choice, ans;
    S:
        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if(n < 0) error("Error reading from socket");
        printf("Server - %s\n", buffer);
        scanf("%d", &num1);
        write(sockfd, &num1, sizeof(int));

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if(n < 0) error("Error reading from socket");
        printf("Server - %s\n", buffer);
        scanf("%d", &num2);
        write(sockfd, &num2, sizeof(int));

        bzero(buffer, 255);
        n = read(sockfd, buffer, 255);
        if(n < 0) error("Error reading from socket");
        printf("Server - %s\n", buffer);
        scanf("%d", &choice);
        write(sockfd, &choice, sizeof(int));

        if(choice == 5)
            goto Q;
        
        read(sockfd, &ans, sizeof(int));
        printf("Server - The answer is: %d\n", ans);
        if(choice != 5)
            goto S;
    Q:
        close(sockfd);
        printf("You have selected to exit.Exit Succeful.");
    return 0;
}