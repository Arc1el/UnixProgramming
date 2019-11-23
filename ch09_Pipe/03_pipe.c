#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
        int fd[2];
        if(pipe(fd) == -1)
        {
                perror("pope");
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
                        {
                        char buf[BUFSIZ + 1];
                        int len;

                        close(fd[1]);

                        write(1, "Chile Process : ", 15);
                        len = read(fd[0], buf, BUFSIZ);
                        buf[strlen(buf)] = '\0';
                        write(1, buf, len);
                        close(fd[0]);
                        break;
                        }
                default :
                        {
                        char *test_str = "Test Message\n";
                        int status;

                        close(fd[0]);

                        write(fd[1], test_str, strlen(test_str));
                        close(fd[1]);
                        waitpid(pid, &status, 0);
                        break;
                        }
        }
        return 0;
}
