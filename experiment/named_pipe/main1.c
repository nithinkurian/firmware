// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void *sending_thread_function(void *arg) {
    char * sender = "/tmp/1to2";
    mkfifo(sender, 0666);
    char data[80];
    int fd;
    while(1)
    {
        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(data, 80, stdin);

        // Open FIFO for write only
        fd = open(sender, O_WRONLY);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, data, strlen(data)+1);
        close(fd);
    }
    pthread_exit(NULL);
}

void *receving_thread_function(void *arg) {
    char * receiver = "/tmp/2to1";
    mkfifo(receiver, 0666);
    char data[80];
    int fd;
    while(1)
    {
        // Open FIFO for write only
        fd = open(receiver, O_RDONLY);

        // Read from FIFO
        read(fd, data, sizeof(data));

        // Print the read message
        printf("Received: %s", data);
        close(fd);
    }
    pthread_exit(NULL);
}


int main()
{
    pthread_t thread_send, thread_receive;
    int thread_arg, result;
    result = pthread_create(&thread_send, NULL, sending_thread_function, &thread_arg);
    if (result != 0) {
        perror("Sending Thread creation failed\n");
        exit(1);
    }

    result = pthread_create(&thread_receive, NULL, receving_thread_function, &thread_arg);
    if (result != 0) {
        perror("Receiving Thread creation failed\n");
        exit(1);
    }

    pthread_join(thread_send, NULL);
    pthread_join(thread_receive, NULL);

    printf("Main thread: All threads completed.\n");
    return 0;
}
