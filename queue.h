#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE 200 //max size of the 1 message
#define MAXPRIORITY 3 //max priority that can be given to a message


// sructure for sending and receiving messages
struct message
{
    long mtype ;
    char message[SIZE+1];
};