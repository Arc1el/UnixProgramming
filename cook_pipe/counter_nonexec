{
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


void kitchen(int fd);
int child_pid = -1;

main(coid)
{
        int c2k_fd[2];
        int k2c_fd[2];

        if(pipe(c2k_fd) == -1)
        {
                perror("pipe");
                exit(1);
        }
        if(pipe(k2c_fd) == -1)
        {
                perror("pipe");
                exit(1);
        }

        child_pid = fork();

        if(child_pid < 0)
        {
                perror("fork");
                exit(2);
        }
        else if(child_pid == 0)
        {
                char success[] = "success";
                close(c2k_fd[1]);
                close(k2c_fd[0]);
                char read_buf[BUFSIZ];
                read(c2k_fd[0], read_buf, BUFSIZ);
                printf("[child] %s\n", read_buf);
                write(k2c_fd[1], success, sizeof(success));
        }
        else
        {
                close(c2k_fd[0]);
                close(k2c_fd[1]);

                char success[] = "success";
                char read_buf[BUFSIZ];

                for(i=0; i<4; i++)
                {
                printf("[parnt] loop start\n");
                write(c2k_fd[1], success, sizeof(success));
                wait();
                read(k2c_fd[0], read_buf, BUFSIZ);
                printf("[parnt] %s\n", read_buf);
                }
        }
}
