#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TIME_FOR_COOK 5

void alrm_handler(int signo)
{
        fprintf(stderr, "[자식] 완성된 요리를 전달합니다.\n\n");
        if(write(1, "success", 7) == -1) //알람시그널이 호출되면 파이프에 success기록
        {
                perror("write 에러 발생");
                exit(2);
        }

        struct sigaction act; //무시했던 시그널 디폴트로 돌려줌
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = SIG_DFL;
        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러발생");
                exit(4);
        }
        if(sigaction(SIGQUIT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러발생");
                exit(4);
        }
}

int main(void)
{
        char buf[BUFSIZ];
        while(1)
        {
                if(read(0, buf, BUFSIZ) != -1) //부모가 파이프로 전송하는경우 동작
                {
                        fprintf(stderr,"[자식] 주문을 전달받았습니다. 메뉴 : %s", buf);

                        struct sigaction act;
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        act.sa_handler = SIG_IGN;
                        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러발생");
                                exit(4);
                        }
                        
                        //알람 시그널 발생시 처리할 핸들러 지정
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        act.sa_handler = alrm_handler;
                        if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러발생");
                                exit(4);
                        }
                        fprintf(stderr,"[자식] 조리를 시작합니다.\n");

                        alarm(TIME_FOR_COOK); //알람발생(핸들러 호출)
                }
        }
        return 0;
}
