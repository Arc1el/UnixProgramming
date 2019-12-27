#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define TIME_FOR_COOK 5

void alrm_handler(int signo)
{
        printf("[자식] 완성된 요리를 전달합니다.\n\n");

        struct sigaction act;
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

        act.sa_handler = SIG_IGN;
        if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction 에러발생");
                exit(4);
        }
}

int main(void)
{
        //파이프 준비 및 파일 디스크립터에 할당
        char *fifo1 = "c2k";
        if(mkfifo(fifo1, 0666) == -1)
        {
                if(errno != EEXIST)
                {
                        fprintf(stderr, "Error in mkfifo %s\n", fifo1);
                        exit(1);
                }
        }
        char *fifo2 = "k2c";
        if(mkfifo(fifo2, 0666) == -1)
        {
                if(errno != EEXIST)
                {
                        fprintf(stderr, "Error in mkfifo %s\n", fifo2);
                        exit(1);
                }
        }
        int sfd;
        if((sfd = open(fifo2, O_WRONLY)) < 0)
        {
                fprintf(stderr, "Error in open %s\n", fifo2);
                exit(2);
        }
        int rfd;
        if((rfd = open(fifo1, O_RDONLY)) < 0)
        {
                fprintf(stderr, "Error in open %s\n", fifo1);
                exit(2);
        }


        int return_read;
        char buf[BUFSIZ];
        return_read = read(rfd, buf, BUFSIZ); //파이프를 통해 부모가 보내온 주문을 buf에 복사
        if(return_read == -1)
        {
                fprintf(stderr, "Error in read");
                exit(3);
        }
        write(sfd, "success", 7); //부모에게 전달할 문자열 sfd파일기술자에 복사
        close(sfd);
        close(rfd);

        printf("\n[자식] %s주문을 전달받았습니다. 조리를 시작합니다.\n", buf);//조리시작

        //주문 조리 시작하는경우 인터럽트 무시
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

        alarm(TIME_FOR_COOK); //알람발생(핸들러 호출)

        sleep(999); //알람이 정상작동하도록 종료 지연
        exit(0);
}
