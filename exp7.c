#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd;
    char data[] = "This is a Linux file operations program.";
    char buffer[100];
    fd = open("sample.txt", O_CREAT | O_RDWR, 0644);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("File created successfully.\n");
    write(fd, data, sizeof(data) - 1);
    printf("Data written successfully.\n");
    lseek(fd, 0, SEEK_SET);
    int n = read(fd, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Data read from file: %s\n", buffer);
    }

    close(fd);
    printf("File closed.\n");
    
    chmod("sample.txt", 0600);
    printf("File permissions changed to 600.\n");

    return 0;
}
