all: chatserve chatclient

chatserve: server.cpp
	g++ -g -Wall -std=c++0x -o chatserve server.cpp

	
chatclient: connect.c 
	gcc -o -std=c99 -o chatclient connect.c  

clean:
	rm server.o


