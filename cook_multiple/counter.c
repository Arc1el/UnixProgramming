#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int pid_child;
int count = 0;

void int_handler(int signo)
{
        kill(pid_child, SIGINT);
        wait();
        printf("\n[부모] 자식프로세스를 종료하였습니다.\n");
        exit(0);
}

void sigusr1_handler(int signo)
{
        printf("[부모] 요리를 전달받아 손님에게 제공하였습니다.\n");
        count--;
        printf("[부모] 현재 진행중인 주문 :  %d\n", count);
        if(count == 0)
        {
                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = int_handler;
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }

                act.sa_handler = SIG_DFL;
                if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }
        }
}

int main(void)
{
        pid_child = fork();
        if(pid_child < 0)
        {
                perror("fork");
                exit(1);
        }
        else if(pid_child == 0)
        {
                if(execl("./kitchen.exe", "kitchen.exe", NULL) < 0)
                {
                        perror ("execl");
                        exit(2);
                }
        }
        else
        {
                char answer;
                struct sigaction act;
                act.sa_flags = 0;
                act.sa_handler = int_handler;
                sigaction(SIGINT, &act, (struct sigaction *)NULL);

                while(1)
                {
                        printf("[부모] 음식을 주문하시겠습니까?"
                                "\n1.피자 2.치킨  3. 햄버거  (숫자입력, 종료 0) : ");
                        scanf("%c", &answer);
                        switch(answer)
                        {
                                case '0' :
                                        printf("[부모] 프로그램을 종료합니다.\n");
                                        exit(0);
                                        break;
                                case '1' :
                                        if(count == 0)
                                        {
                                                act.sa_handler = SIG_IGN;
                                                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }

                                                act.sa_handler = sigusr1_handler;
                                                if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }
                                        }
                                        count++;
                                        kill (pid_child, SIGUSR1);
                                        printf("\n[부모] 피자주문을  전달합니다.\n");
                                        break;
                                case '2' :
                                        if(count == 0)
                                        {
                                                act.sa_handler = SIG_IGN;
                                                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }

                                                act.sa_handler = sigusr1_handler;
                                                if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }
                                        }
                                        count++;
                                        kill (pid_child, SIGUSR2);
                                        printf("\n[부모] 치킨주문을  전달합니다.\n");
                                        break;
                                case '3' :
                                        if(count == 0)
                                        {
                                                act.sa_handler = SIG_IGN;
                                                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }

                                                act.sa_handler = sigusr1_handler;
                                                if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                                                {
                                                        perror("sigaction error");
                                                        exit(3);
                                                }
                                        }
                                        count++;
                                        kill (pid_child, SIGRTMIN);
                                        printf("\n[부모] 햄버거주문을  전달합니다.\n");
                                        break;
                        }
                }
        }
        return 0;
}
