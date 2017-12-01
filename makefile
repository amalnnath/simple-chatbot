# build an executable named server-socket from serverSocket.c
all: serverSocket.c 
	gcc -g -Wall -o server-socket serverSocket.c
	
clean: 
	$(RM) server-socket
