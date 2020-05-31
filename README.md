# Message_queues
Program to handle requests provided as messages, with each request entailing a priority (between 1 and 3 included, 1 being the highest priority) and a data of type char []

This program contains 3 files server program.c , client program.c and queue.h.

**server_program.c** has 4 functions besides main(). These are: create queue(),
access queue(), remove queue(), handle().

+ create_queue() function is used to create new message queue
+ access_queue() function is used to access message queue that is created by
create_queue() function
+ remove_queue() function is used to remove message queue with given id
+ handle() function is used to handle messages given by the user from ter-
minal

**client_program.c** has 4 functions besides main(). These are: create_queue(),
access_queue(), print_msg(), receive().

+ create_queue() function is used to create new message queue
+ access_queue() function is used to access message queue that is created by
create_queue() function
+ print_msg() function is used to print the received message with its priority
+ receive() function is used to receive the messages from the message queue
with given id

**queue.h** is the header file that contains message structure used by both server program.c
and client program.c 

### Usage

Firstly each .c file have to be compiled. Then by executing server program user
can enter his message with priority. 

**Example:** 1 hi there. So, here ”1” is
the priority of the message and ”hi there” is our message. After writing some
messages the user can execute client program to receive the messages in order
with their priority.
