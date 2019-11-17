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
}
/*************************************************************************/
void sigusr1_handler(int signo)
{
        printf("---------- child process ----------\n");
        printf("주문이 접수되었습니다.\n");

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = alrm_handler;

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
        act.sa_flags = 0;
        act.sa_handler = sigusr1_handler;

        //SIGALRM, SIGUSR1을 제외한 모든시그널 블록
        sigset_t block;
        sigfillset(&block);
        sigdelset(&block, SIGALRM);
        sigdelset(&block, SIGUSR1);
        sigprocmask(SIG_SETMASK, &block, NULL);

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
