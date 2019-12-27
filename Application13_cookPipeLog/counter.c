#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>

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
        time_t t;
        struct tm tm;

        char *fifo1 = "c2k";
        if(mkfifo(fifo1, 0666) == -1)
        {
                if(errno != EEXIST)
                {
                        fprintf(stderr, "Error in mkfifo %s\n", fifo1);
                        exit(2);
                }
        }
        char *fifo2 = "k2c";
        if(mkfifo(fifo2, 0666) == -1)
        {
                if(errno != EEXIST)
                {
                        fprintf(stderr, "Error in mkfifo %s\n", fifo2);
                        exit(2);
                }
        }
        int time_fd;
        time_fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND , 0644 );
        if(time_fd == -1)
        {
                perror("open log file");
                exit(6);
        }

        while(1)
        {

                pid_child = fork();
                if(pid_child < 0) //fork 오류
                {
                        perror("fork");
                        exit(2);
                }
                else if(pid_child == 0) //자식프로세스
                {
                        if(execl("./kitchen.exe", "kitchen.exe", NULL) < 0)
                        {
                                perror("execl");
                                exit(2);
                        }
                }

                else
                {       //주문전 인터럽트 발생시 정상동작 핸들러 등록, 음식 완료후 인터럽트 발생시 정상동작
                        struct sigaction act;
                        sigemptyset(&act.sa_mask);
                        act.sa_flags = 0;
                        act.sa_handler = int_handler;
                        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                        {
                                perror("sigaction 에러 발생");
                                exit(3);
                        }


                        char answer;
                        char menu[MENU_SIZE];
                        printf("[부모] 주문하실 메뉴를 입력해주세요 (문자열)  : ");
                        fgets(menu, MENU_SIZE, stdin);
                        menu[strlen(menu)-1] = 0;

                        int rfd; //읽기용 파이프 준비
                        if((rfd = open(fifo2, O_RDONLY)) < 0)
                        {
                                fprintf(stderr, "Error in open %s\n", fifo2);
                                exit(4);
                        }
                        int sfd; //쓰기용 파이프 준비
                        if((sfd = open(fifo1, O_WRONLY)) < 0)
                        {
                                fprintf(stderr, "Error in open %s\n", fifo1);
                                exit(4);
                        }

                        if(write(sfd, menu, MENU_SIZE) == MENU_SIZE) // 입력받은 메뉴를 파이프에 기록 (주문보내기)
                        {
                                close(sfd);
                                t = time(NULL);
                                tm = *localtime(&t);
                                char logbuf[BUFSIZ];
                                sprintf(logbuf, "%d년 %d월 %d일 %d시 %d분 %d초 주문전달 (메뉴 : %s)\n",
                                                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, menu);
                                write(time_fd, logbuf, strlen(logbuf));
                        }
                        else
                        {
                                perror("write");
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

                        wait(); //자식이 종료되어 반환될때까지 대기

                        int return_read;
                        char buf[BUFSIZ];
                        return_read = read(rfd, buf, BUFSIZ); //자식이 기록한 파이프의 내용을 buf에 복사
                        close(rfd);

                        if(return_read == -1) //read실패시
                        {
                                fprintf(stderr,"read오류");
                                exit(5);
                        }
                        else //read성공시
                        {
                                if(strcmp("success", buf) == 0)
                                {
                                printf("[부모] 손님에게 요리를 제공하였습니다.\n");

                                t = time(NULL);
                                tm = *localtime(&t);
                                char logbuf[BUFSIZ];
                                sprintf(logbuf, "%d년 %d월 %d일 %d시 %d분 %d초 주문완료\n",
                                                tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                                write(time_fd, logbuf, strlen(logbuf));
                                }
                                else
                                {
                                        fprintf(stderr, "문자열 길이가 같지 않음");
                                        exit(6);
                                }
                        }

                }
        }
        return 0;
}
