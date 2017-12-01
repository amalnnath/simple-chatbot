/*
    Amalnnath Parameswaran
    100585138
    Systems Programming
    Assignment Two
    Task 2
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
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
     
    //Accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {

        printf("%s\n%lu\n", client_message, strlen(client_message));

        if(0 == strcmp(client_message, "Hello")){
            write(client_sock , "Hi! What can I do for you?", 26);
        }
        else if(0 == strcmp(client_message, "What's your name?")){
            write(client_sock , "My name is Drew! What's yours?", 30);
        }
        else if(0 == strcmp(client_message, "How old are you?")){
            write(client_sock , "I'm old enough... Can we change the topic?", 42);
        }
        else if(0 == strcmp(client_message, "What is the answer to life?")){
            write(client_sock , "42, obviously!", 14);
        }
        else if(0 == strcmp(client_message, "Who made you?")){
            write(client_sock , "Amalnnath did! He's a really smart student at UOIT!", 51);
        }
        else if(0 == strcmp(client_message, "-help")){
            write(client_sock , "These are the only messages I can currently answer to!\n", 55);
            write(client_sock , "1) Hello\n", 9);
            write(client_sock , "2) What's your name?\n", 21);
            write(client_sock , "3) How old are you?\n", 20);
            write(client_sock , "4) What is the answer to life?\n", 31);
            write(client_sock , "5) Who made you?", 17);
        }
        else{
            write(client_sock , "I'm sorry, I didn't understand what you said!" , 45);
        }

        memset(client_message, 0, 2000);
        read_size = 1;
    }
     
    if(read_size == 0){

        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}