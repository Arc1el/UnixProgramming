#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

#define MENU_SIZE 128

int pid_child = -1;

void int_handler(int signo)
{
        kill(pid_child, SIGINT); //자식종료
        printf("\n\n[부모] 자식 프로세스를 종료하였습니다.\n");
        printf("[부모] 자신을 종료합니다.\n");
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

        if(pid_child < 0) //fork 오류
        {
                perror("fork");
                exit(2);
        }
        else if(pid_child == 0) //자식프로세스
        {
                close(c2k_fd[1]);
                close(k2c_fd[0]);

                dup2(c2k_fd[0], 0); // stdin -> c2k_fd[0]
                dup2(k2c_fd[1], 1); // stdout -> k2c_fd[1]

                if(execl("./kitchen.exe", "kitchen.exe", NULL) < 0)
                {
                        perror("execl");
                        exit(2);
                }
        }

        else
        {
                close(c2k_fd[0]);
                close(k2c_fd[1]);

                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = int_handler;
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction 에러 발생");
                        exit(3);
                }
                int i;
                char menu[MENU_SIZE];
                while(1)
                {
                        printf("[부모] 주문하실 메뉴를 입력해주세요 (문자열)  : ");
                        fgets(menu, MENU_SIZE, stdin);
                        write(c2k_fd[1], menu, strlen(menu));

                        act.sa_handler = SIG_IGN; //요리 완료전 SIGINT, SIGQUIT 무시
                        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러 발생");
                                exit(3);
                        }
                        if(sigaction(SIGQUIT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러 발생");
                                exit(3);
                        }

                        char buf[BUFSIZ];
                        fprintf(stderr, "XXX\n");

                        read(k2c_fd[0], buf, BUFSIZ);
                        prLintf("%s\n", buf);
                }
        }
        return 0;
}
