# simple-chatbot
Simple chatbot designed for course assignment.

### **Documentation:**
For task two, we were asked to implement a simple "chatbot" using "Sockets". And that is how Drew (the chatbot) was created.

For the most part, i did stick with the sample, although I did change a couple things to improve the program's functionalities. I first noticed that for lines with spaces, example "How are you?", it would send each word seperately, so to bypass this, i used fgets instead of scanf. The problem with fgets is that to recognize when a line has ended, it adds an extra character to the end. Therefore to remove it, I used the `strcspn` to correct that.

```
printf("Me: ");
fgets(message, 2000, stdin);
message[strcspn(message, "\n")] = '\0';
```

Another thing I noticed when working on this task was if the message was 5 letters. For example, "Hello", and then my next message was less than 5 letters "Hey", it would send "Heylo" because it would overwrite the previous message. To overcome this, I added:

```
memset(server_reply, 0, 2000);
```

This essentially clears the variable evrytime so that there is nothing being overwritten.

The code that determines how to respond to messages is listed below.
```
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
```

The heart of the code is essentially a huge if statement within a while loop. while it is running, it recieves messages and compares it with all the phrases specified. If one of the phrases matches, it will respond with that predetermined return. Otherwise, it will run the `else` statement claiming that it did not understand what you tried to ask. If you send the message '-help', the chatbot will list the questions that it is able to answer.
