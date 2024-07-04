#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include <errno.h>
#include <windows.h>

#define SERVER_REPLY_SIZE 40000
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv){
    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in server_address;
    int server_fd /*file descriptor*/, recv_size;
    char* message, server_reply[SERVER_REPLY_SIZE];

    printf("\nStarting server");
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("hi\n");

    if((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("Socket creation failed: %d\n", WSAGetLastError());
    }
    printf("socket created\n");

    server_address.sin_addr.s_addr = inet_addr("142.250.65.174"); /*googles ip address*/
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);

    //Connect to remote server
	if (connect(s , (struct sockaddr *)&server_address , sizeof(server_address)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
	
	//Send some data
	message = "GET / HTTP/1.1\r\n\r\n";
	if( send(s , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

    //Receive a reply from the server
	if((recv_size = recv(s , server_reply , SERVER_REPLY_SIZE , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	
	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
    FILE* output = fopen("webpage.html","w");
	fprintf(output, server_reply);

	return 0;
}