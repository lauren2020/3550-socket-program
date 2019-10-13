#include "headerFiles.h"
//#define SERVER_PORT 51962

int main(int argc, char* argv[]) {
    // Declare and define variables
    printf("Starting program...");
    int s;
    int len;
    char* servName;
    int servPort;
    char* string;
    char buffer[256+1];
    struct sockaddr_in servAddr;
    // Check and set program arguments
    //printf("\nargc: %d", argc);
    if (argc < 4) {
        printf("Error: three arguments are neded!");
        exit(1);
    }
    //printf("\nSetting info");
    servName = argv[1];
    servPort = atoi(argv[2]);
    string = argv[3];
    //printf("\nInfo Recieved: %s %d %s", servName, servPort, string);
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
//    // Send echo string
    len = sendto(s, string, strlen(string), 0, (struct sockaddr *) &servAddr, sizeof(servAddr));
    //Recieve echo string
    recvfrom(s, buffer, len, 0, NULL, NULL);
    //Print and verify echoed string
    buffer[len] = '\0';
    printf("\nRecieved: ");
    fputs(buffer, stdout);
    close(s);
    exit(0);
}
