FLAGS =  -Wall -pthread
LIBS = -lpthread 
CC = gcc  

all: server client 

server: echoServer.c
	gcc -o echoServer echoServer.c $(FLAGS) $(LIBS)
client: echoClient.c
	cc  -o echoClient echoClient.c $(FLAGS) $(LIBS)




 
