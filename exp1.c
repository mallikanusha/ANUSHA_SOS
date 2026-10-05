#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    int fd;
    char buffer[100];
    char message[] = "Hello from write() system call!\n";

    printf("=== Basic Linux System Calls ===\n\n");
    printf("Process ID (getpid): %d\n", getpid());

    printf("Parent Process ID (getppid): %d\n\n", getppid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n\n", getppid());

        write(STDOUT_FILENO, message, sizeof(message) - 1);

        return 0;
    }
    else
    {
        
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n\n", pid);
        wait(NULL);
        fd = open("systemcall.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

        if (fd < 0)
        {
            perror("open failed");
            return 1;
        }
        write(fd, "Linux System Calls Demonstration\n", 33);

        close(fd);

        printf("File created and written using open(), write(), and close().\n");

        fd = open("systemcall.txt", O_RDONLY);

        if (fd < 0)
        {
            perror("open failed");
            return 1;
        }
        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0)
        {
            buffer[n] = '\0';
            printf("\nData read from file:\n%s", buffer);
        }

        close(fd);
    }

    return 0;
}
