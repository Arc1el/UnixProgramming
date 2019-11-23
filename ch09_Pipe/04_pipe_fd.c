#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
        int fd[2];

        if(pipe(fd) == -1)
        {
                perror("pipe");
                exit(1);
        }

        pid_t pid;
        switch(pid = fork())
        {
                case -1 :
                        perror("fork");
                        exit(1);
                        break;
                case 0  :
                        close(fd[1]);
                        if(fd[0] != 0)
                        {
                                dup2(fd[0], 0);
                                close(fd[0]);
                        }
                        execlp("grep", "grep", "telnet", (char *)NULL);
                        exit(1);
                        break;
                default :
                        close(fd[0]);
                        if(fd[1] != 1)
                        {
                                dup2(fd[1], 1);
                                close(fd[1]);
                        }
                        execlp("ps", "ps", "-ef", (char *)NULL);
                        wait(NULL);
                        break;
        }
        return 0;
}
