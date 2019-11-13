#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
        int fd, flags;

        fd=open("unix.txt", O_RDWR);
        if(fd==-1)
        {
                perror("open");
                exit(1);
        }

        if ((flags=fcntl(fd,F_GETFL)) == -1)
        {
                perror("fcntl");
                exit(1);
        }

        flags |= O_APPEND;

        if (fcntl(fd, F_SETFL, flags) == -1)
        {
                perror("fcntl");
                exit(1);
        }

        if(write(fd, "Mokpo National Maritime University\n", 35) !=35)
        {
                perror("Write");
        }
        close(fd);

        return 0;
}