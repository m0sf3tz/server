#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<netinet/in.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdint.h>

#include "projectDefines.h"
#include "buffApp.h"
#include "shiftParser.h"


int main(int argc , char *argv[])
{
    //initialize the byte digestor
    initRxDigestor();
    //initialize the shift parser
    initShiftParser();
    
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    pthread_t tid;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    //used as a temp holding block before starting a new thread to process data
    char client_message[TOTAL_BYTES_IN_SECTOR];
    
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , TOTAL_BYTES_IN_SECTOR , 0)) > 0 )
    {
        int counter = 0;
        while(counter != read_size)
        {
            processIncomingData(client_message[counter++]);
        }
    }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}
