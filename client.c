//
// Created by root on 10/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUFFER 1024

int main(){
    int clntSock;
    struct sockaddr_in servAddr;
    char *servIP = "127.0.0.1";
    char *string;
    int stringLen;
    int totalBytesRcvd,bytesRcvd;

    if ((clntSock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
        printf("error here at socket creation");

    memset(&servAddr,0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8877);
    servAddr.sin_addr.s_addr = inet_addr(servIP);
    if (connect(clntSock,(struct sockaddr *)&servAddr, sizeof(servAddr))<0)
        printf("error in connection making");
    //memset(string,'\0', sizeof(string));
    string = "Hello";
    stringLen = strlen(string);
    if (send(clntSock,string,stringLen,0) != stringLen)
        printf("Error in sending Data");

    int n = 0;
    int len = 0, maxlen = 100;
    char buffer[maxlen];
    char* pbuffer = buffer;

    // will remain open until the server terminates the connection
    while ((n = recv(clntSock, pbuffer, maxlen, 0)) > 0) {
        pbuffer += n;
        maxlen -= n;
        len += n;

        buffer[len] = '\0';
        printf("received: '%s'\n", buffer);
    }
    close(clntSock);

    return 0;
}

//#include <arpa/inet.h>
//#include <stdio.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <unistd.h>
//
//int main() {
//    const char* server_name = "localhost";
//    const int server_port = 8877;
//
//    struct sockaddr_in server_address;
//    memset(&server_address, 0, sizeof(server_address));
//    server_address.sin_family = AF_INET;
//
//    // creates binary representation of server name
//    // and stores it as sin_addr
//    // http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
//    inet_pton(AF_INET, server_name, &server_address.sin_addr);
//
//    // htons: port in network order format
//    server_address.sin_port = htons(server_port);
//
//    // open a stream socket
//    int sock;
//    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
//        printf("could not create socket\n");
//        return 1;
//    }
//
//    // TCP is connection oriented, a reliable connection
//    // **must** be established before any data is exchanged
//    if (connect(sock, (struct sockaddr*)&server_address,
//                sizeof(server_address)) < 0) {
//        printf("could not connect to server\n");
//        return 1;
//    }
//
//    // send
//
//    // data that will be sent to the server
//    const char* data_to_send = "Gangadhar Hi Shaktimaan hai";
//    send(sock, data_to_send, strlen(data_to_send), 0);
//
//    // receive
//
//    int n = 0;
//    int len = 0, maxlen = 100;
//    char buffer[maxlen];
//    char* pbuffer = buffer;
//
//    // will remain open until the server terminates the connection
//    while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
//        pbuffer += n;
//        maxlen -= n;
//        len += n;
//
//        buffer[len] = '\0';
//        printf("received: '%s'\n", buffer);
//    }
//
//    // close the socket
//    close(sock);
//    return 0;
//}