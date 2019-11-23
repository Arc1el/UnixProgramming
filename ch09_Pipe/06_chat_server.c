#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
        int pd, n;

        printf("Server =====\n");

        if(argc < 2)
        {
                fprintf(stderr, "Usage : %s message\n", argv[0]);
                exit(1);
        }
        char *msg = argv[1];
        printf("To Client : %s\n", msg);

        if(mkfifo("./test_fifo", 0666) == -1)
        {
                perror("mkfifo");
                exit(2);
        }
        printf("make success");

        if((pd = open("./test_fifo", O_WRONLY)) == -1)
        {
                perror("open");
                exit(3);
        }
        printf("open success");

        n = write(pd, msg, strlen(msg)+1);
        if(n == -1)
        {
                perror("write");
                exit(4);
        }
        close(pd);



        return 0;
}
