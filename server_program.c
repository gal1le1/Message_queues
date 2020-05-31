#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// removes the queue with provided id
void remove_queue (int id)
{
    int r;
    r = msgctl(id, IPC_RMID, NULL);
    if (r == -1){
        perror("Msgctl");
        exit(1);
    }
}

// function takes the message and its priority
int handle(char *message, int priority){

    // checks if the priority is out of range or not
    if (priority > MAXPRIORITY || priority < 0)
    {
        printf("Priority is out of range\n");
        exit(1);
    }
    // checks message size
    if (strlen(message) > SIZE)
    {
        printf("Message is too long\n");
        exit(1);
    }

    struct message msg;
    int q_id = access_queue();
    printf("Accessing queue with id: %d\n", q_id);
    msg.mtype = (long)priority;
    strncpy(msg.message, message, SIZE);

    // sends the msg to specified queue with id. In case of error or succes it shows the result 
    if (msgsnd(q_id, &msg, strlen(message), 0) == -1)
    {
        perror("Message send");
    }
    else
    {
        printf("Message: \"%s\" handled with priority: %d. Queue id: %d\n", msg.message, priority, q_id);
    }

    return 0;

}


int main(int argc, char const *argv[])
{
    int qid = create_queue();
    printf("Creating queue with id: %d\n", qid);
    char text[SIZE+1];
    char *token;
    int prior, handled;
    
    // takes message and its priority
    while (fgets (text, SIZE, stdin))
    {
        //In case of pressing enter-new line (means message of size 0) it removes the queue and terminates 
        if (strcmp(text, "\n") == 0)
        {
            remove_queue(qid);
            break;
        }
        // parses message and priority
        token = strtok(text, " ");
        prior = atoi(token);

        token = strtok(NULL, "\0");
        token[strlen(token)-1] = '\0';

        // sends message and its priority to handle function
        handled = handle(token, prior);

    }
    

    return 0;
}

