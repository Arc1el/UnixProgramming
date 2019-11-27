#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int pid_child;
void int_handler(int signo)
{
        kill(pid_child, SIGINT); //자식종료
        printf("\n자식 프로세스를 종료하였습니다.\n");
        exit(0);
}

int main(void)
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

        pid_child = fork();

        if(pid_child < 0)
        {
                perror("fork 에러발생");
                exit(1);
        }
        else if(pid_child == 0)
        {
                close(c2k_fd[1]);
                close(k2c_fd[0]);

                dup2(c2k_fd[0], 0);
                dup2(k2c_fd[1], 1);

                if(execl("./kitchen.exe", "kitchen.exe", c2k_fd, NULL) < 0)
                {
                        perror("execl 에러 발생");
                        exit(2);
                }
        }
        else
        {
                while(1)
                {
                        close(c2k_fd[0]);
                        close(k2c_fd[1]);
                        struct sigaction act;
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        act.sa_handler = int_handler;
                        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaciton 에러 발생");
                                exit(3);
                        }
                        printf("주문하시겠습니까? (y) ");
                        int ch;
                        while((ch = fgetc(stdin)) && ((ch != 'y') && (ch != 'Y')));
                        if((ch =='y') || (ch == 'Y'))
                        {
                                int status;
                                char string[BUFSIZ];
                                read(k2c_fd[0], string, sizeof(string));
                                printf("%s", string);
                        }
                        printf("\n");
                }
        }
}
