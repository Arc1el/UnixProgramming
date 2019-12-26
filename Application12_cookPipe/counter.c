#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
                close(c2k_fd[0]);
                close(k2c_fd[1]);
        }
        else
        {
                close(c2k_fd[0]);
                close(k2c_fd[1]);

                char menu[MENU_SIZE];
                while(1)
                {
                        struct sigaction act; //메뉴 동작 전 인터럽트 발생시 핸들러처리하도록
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        act.sa_handler = int_handler;
                        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러 발생");
                                exit(3);
                        }

                        printf("[부모] 주문하실 메뉴를 입력해주세요 (문자열)  : ");
                        fgets(menu, MENU_SIZE, stdin);
                        if(write(c2k_fd[1], menu, strlen(menu)) != -1) //파이프에 쓰기성공시
                        {
                                printf("[부모] 메뉴를 전달하였습니다.\n\n");
                        }
                        else
                        {
                                perror("write 에러 발생");
                                exit(4);
                        }

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

                        //after child process
                        
                        char buf[BUFSIZ];
                        if(read(k2c_fd[0], buf, BUFSIZ) != -1) //자식에게 파이프로 완료를 전달받았을때
                        {
                                if(strncmp("success", buf, 7) == 0)
                                {
                                        printf("[부모] 메뉴를 전달받아 손님에게 제공하였습니다.\n");
                                }
                        }
                        else
                        {
                                perror("read 에러 발생");
                                exit(5);
                        }
                }
                close(c2k_fd[1]);
                close(k2c_fd[0]);
        }
        return 0;
}
