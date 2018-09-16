FLAGS =  -Wall -pthread
LIBS = -lpthread 
CC = gcc  

all:
	gcc -o server srv.c shiftParser.c buffApp.c $(FLAGS) $(LIBS)
