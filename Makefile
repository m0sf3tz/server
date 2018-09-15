FLAGS =  -Wall -pthread
LIBS = -lpthread 
CC = gcc  

all: server client 

server: server.c
	gcc -o server server.c shiftParser.c buffApp.c $(FLAGS) $(LIBS)
client: echoClient.c
	cc  -o echoClient echoClient.c $(FLAGS) $(LIBS)




 
