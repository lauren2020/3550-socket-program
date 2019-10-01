#include "headerFiles.h"
#define SERVER_PORT 51962

int main(void) {
    // Declare and define variables
    printf("Server started.");
    int breakWhile = 0;
    int s;
    int len;
    char buffer[256];
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    socklen_t clntAddrLen;
    // Build local server socket address
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT);
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
    
    while (breakWhile == 0) {
        len = recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *) &clntAddr, &clntAddrLen);
        sendto(s, buffer, len, 0, (struct sockaddr *) &clntAddr, sizeof(clntAddr));
    }
}
