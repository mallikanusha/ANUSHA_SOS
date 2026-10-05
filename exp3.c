#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t shm_key, msg_key;
    int shmid, msgid;
    char *shared_memory;
    struct message msg;
    shm_key = ftok("shmfile", 65);
    msg_key = ftok("msgfile", 75);

    shmid = shmget(shm_key, 1024, 0666 | IPC_CREAT);

    shared_memory = (char *)shmat(shmid, NULL, 0);

    
    msgid = msgget(msg_key, 0666 | IPC_CREAT);

    if (shmid == -1 || shared_memory == (char *)-1 || msgid == -1) {
        perror("IPC creation failed");
        exit(1);
    }

    if (fork() == 0) {

        strcpy(shared_memory, "Hello from Child using Shared Memory!");

        printf("Child: Data written to Shared Memory.\n");

        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello from Child using Message Queue!");

        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

        printf("Child: Message sent using Message Queue.\n");

      
        shmdt(shared_memory);

        exit(0);
    }
    else {
        wait(NULL);
        printf("\nParent: Reading from Shared Memory:\n");
        printf("%s\n", shared_memory);

        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);

        printf("\nParent: Reading from Message Queue:\n");
        printf("%s\n", msg.msg_text);

        shmdt(shared_memory);

        shmctl(shmid, IPC_RMID, NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
