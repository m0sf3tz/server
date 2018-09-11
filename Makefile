FLAGS =  -Wall -pthread
LIBS = -lpthread 
CC = gcc  

all: server client 

server: echoServer.c
	cc -o echoServer echoServer.c 
client: echoClient.c
	cc -o echoClient echoClient.c

 
