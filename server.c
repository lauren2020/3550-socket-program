#include "headerFiles.h"
#define SERVER_PORT 51962

int main(int argc, char* argv[]) {
    // Declare and define variables
    printf("Server started.");
    int breakWhile = 0;
    int s;
    int port = 3000;
    int len;
    int len1 = 10;
    char buffer[256];
    char buffer1[256] = "testreturn";
    //char* string;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    
    if (argc < 2) {
        printf("Error: port number and return phrase are required");
        exit(1);
    }
    port = atoi(argv[1]);
    //string = argv[2];
    //len1 = sizeof(buffer1) / sizeof(int);
    
    socklen_t clntAddrLen;
    // Build local server socket address
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Create socket
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error: socket failed!");
        exit(1);
    }
    // Bind socketto local address and port
    if ((bind(s, (struct sockaddr *) &servAddr, sizeof(servAddr))) < 0) {
        perror("Error: bind failed!");
        exit(1);
    }
    printf("\nListening on port %d", port);
    printf("\n");
    
    while (breakWhile == 0) {
        len = recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *) &clntAddr, &clntAddrLen);
        printf("Recieved %s", buffer);
        sendto(s, buffer1, len1, 0, (struct sockaddr *) &clntAddr, sizeof(clntAddr));
        printf("\n");
    }
}
