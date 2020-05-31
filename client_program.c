#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// function creates queue and returns its id 
int create_queue (void)
{
    key_t key;
    int id;

    key = ftok("/etc/passwd", 'F'); //ftok function genarates the key. Note: server and client agree on the same file
    if (key == -1){
        perror("Key");
        exit(1);
    }    

    // generating the queue id. If the resource doesn't exists it will create it with the help of "IPC_CREAT"
    id = msgget(key, IPC_CREAT | 0666);
    if (id == -1){
        perror("Msgget");
        exit(1);
    }

    return id;
}

// acccessing the queue that is already generated
int access_queue (void)
{
    key_t key ;
    int id ;
    key = ftok("/etc/passwd", 'F');
    if (key == -1){
        perror("Key");
        exit(1);
    }

    id = msgget(key, 0);
    if (id == -1){
        perror("Msgget");
        exit(1);
    }
    return id;
}

//prints the received message with its priority
void print_msg(struct message *msg){
    printf("Received message: \"%s\" with Priority: %ld\n", msg->message, msg->mtype);
    printf("\n");
}

//receives the messages from the message queue with given id
void receive(){
    struct message rec_msg;
    int q_id = access_queue();
    int msg_len;
    printf("Accessing queue with id: %d\n", q_id);

    for (;;)
    {
        //receives the message with specified id. With msgtype < 0 first message in the queue with the lowest type value is read
        if ((msg_len = msgrcv(q_id, &rec_msg, SIZE, (-1 * MAXPRIORITY), MSG_NOERROR)) == -1)
        {
            perror("Receive message");
            printf("0\n");
            exit(1);
        }
        else
        {
            rec_msg.message[msg_len] = '\0';
            print_msg(&rec_msg);            
        }   
    }
}



int main(int argc, char const *argv[])
{
    int qid = create_queue();
    printf("Creating queue with id: %d\n", qid);

    // starts receiving messages
    receive();

    return 0;
}
