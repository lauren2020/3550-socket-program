#include "headerFiles.h"

int main(int argc, char* argv[]) {
    // Declare and define variables
    int s;
    int len;
    char* servName;
    int servPort;
    char* string;
    char buffer[256+1];
    struct sockaddr_in servAddr;
    // Check and set program arguments
    if (argc < 4) {
        printf("Error: three arguments are neded!");
        exit(1);
    }
    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];
    // Bind server socket address
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    inet_pton(AF_INET, servName, &servAddr.sin_addr);
    servAddr.sin_port = htons(servPort);
    // Create socket
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("\nError: Socket failed!");
        exit(1);
    }
    // Send echo string
    len = sendto(s, string, strlen(string), 0, (struct sockaddr *) &servAddr, sizeof(servAddr));
    
    //Recieve echo string
    char len_buffer[256+1];
    recvfrom(s, len_buffer, 2, 0, NULL, NULL);
    int new_len = atoi(len_buffer);

    recvfrom(s, buffer, new_len, 0, NULL, NULL);
    
    //Print and verify echoed string
    buffer[new_len] = '\0';
    printf("\nRecieved: %s", buffer);
    close(s);
    exit(0);
}
