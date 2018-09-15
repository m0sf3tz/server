#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<netinet/in.h>
#include <sys/socket.h>




int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000];
    pthread_t tid;
    

        
    char * ptrIter = message;
    int counter =0;
    for(counter =0 ; counter < 1000; counter++)
    {
        message[counter] = counter;
    }
   
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     

   
    //Send some data
    if( send(sock , message , 1000 , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
         
    sleep(10);
     
    close(sock);
    return 0;
}
