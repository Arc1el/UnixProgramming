#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

#define TIME_FOR_COOK 3

void sigusr1_handler(int signo);


/*************************************************************************/
void alrm_handler(int signo)
{       //요리가 완성됨을 출력
        printf("완성된 요리를 전달합니다.\n");
        kill(getppid(), SIGUSR1); //부모에게 SIGUSR1시그널을 보냄

        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = SIG_DFL;
        int signum;
        for(signum=1; signum<=40; signum++) //모든시그널 무시를 디폴트 동작으로 되돌림
        {
                sigaction(signum, &act, (struct sigaction *)NULL);
        }

        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = sigusr1_handler;
        if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러 발생");
                exit(1);
        }
}
/*************************************************************************/
void sigusr1_handler(int signo)
{
        printf("---------- child process ----------\n");
        printf("주문이 접수되었습니다.\n");

        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = SIG_IGN;
        int signum;
        for(signum=1; signum<=40; signum++) //SIGALRM을 제외한 모든 시그널 무시
        {
                if((signum != SIGALRM) && (signum != 9) && (signum != 19))
                {
                        sigaction(signum, &act, (struct sigaction *)NULL);
                }
        }

        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = alrm_handler;
        if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러발생");
                exit(1);
        }

        //ALRM시그널 받을경우 알람핸들러 호출
        if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러 발생");
                exit(1);
        }
        //일정 조리시간 후 SIGALRM시그널을 보냄(알람핸들러 호출)
        alarm(TIME_FOR_COOK);
}
/*************************************************************************/

int main(void)
{

        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = sigusr1_handler;

        //부모로부터 SIGUSR1을 받아오면 조리시작(핸들러 호출)
        if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러 발생");
                exit(1);
        }

        while(1)
        {
                sleep(999);     //시그널 발생까지 대기
        }

        return 0;
}
