#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

int pid_child; //자식의 pid를 할당하기 위한 전역변수 pid_child선언
/********************************************************************/
void int_handler(int signo)
{
        //주문이 없는상태에서 SIGINT 또는 SIGQUIT시그널이 오는경우
        kill(pid_child, SIGINT); //자식종료
        printf("\n자식 프로세스를 종료하였습니다.\n");
        exit(0); //자신종료
}
/********************************************************************/
void sigusr1_handler(int signo)
{
        //자식으로부터 SIGUSR1 시그널이 오면 요리 제공
        printf("---------- parent process ----------\n");
        printf("완성된 요리를 전달받아 손님에게 제공하였습니다.\n");

        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = int_handler; //SIGINT가 오는경우 다시 int_handler로 동작
        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러 발생");
                exit(3);
        }
}
/********************************************************************/

int main(void)
{

        pid_child = fork();

        if(pid_child < 0)
        {
                perror("fork 에러발생");
                exit(1);
        }
        //자식프로세스인경우 exec로 프로그램의 몸체를 c_cook.exe로 변경 
        else if(pid_child == 0)
        {
                if(execl("./c_cook.exe", "c_cook.exe", NULL) < 0)
                {
                        perror("execl 에러 발생");
                        exit(2);
                }
        }

        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = int_handler;
        //주문전 SIGINT시그널 발생하는경우
        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaciton 에러 발생");
                exit(3);
        }

        while(1)        //반복해서 메뉴출력
        {
                printf("---------- parent process ----------\n");
                printf("음식을 주문하시겠습니까? (y/n) : ");
                char answer;
                scanf("%c", &answer);

                switch(answer)
                {
                        case 'Y' :
                        case 'y' : //주문이 들어오면 SIGUSR1을 제외한 모든시그널 블록
                                sigemptyset(&act.sa_mask);
                                act.sa_flags = 0;
                                act.sa_handler = sigusr1_handler;
                                sigaction(SIGUSR1, &act, NULL);
                                //사용자로부터 주문받아 자식프로세스에게 주문전달
                                if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                                {
                                        perror("sigaction 에러 발생");
                                        exit(3);
                                }

                                sigemptyset(&act.sa_mask);
                                act.sa_flags = 0;
                                act.sa_handler = SIG_IGN;
                                int signum;
                                for(signum=1; signum<=40; signum++) //SIGUSR1을 제외한 모든 시그널 무시
                                {
                                        if(signum != SIGUSR1)
                                        {
                                        sigaction(signum, &act, NULL);
                                        }
                                }

                                kill(pid_child, SIGUSR1); //자식에게 SIGUSR1 시그널 보냄
                                printf("주문을 요청하였습니다.\n");
                                pause();
                                break;
                        case 'N':
                        case 'n':
                                printf("주문프로그램을 종료합니다.\n");
                                exit(0);
                        default :
                                printf("잘못된 입력입니다. y or n\n");
                                exit(4);
                }
                getchar();
        }
}
