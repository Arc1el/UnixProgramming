
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>

#define MENU_SIZE 128

int pid_child;
void int_handler(int signo)
{
        kill(pid_child, SIGINT); //자식종료
        printf("\n자식 프로세스를 종료하였습니다.\n");
        exit(0);
}

int main(void)
{
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

        pid_child = fork();

        if(pid_child < 0)
        {
                perror("fork");
                exit(2);
        }
        else if(pid_child == 0)
        {
                if(execl("./kitchen.exe", "kitchen.exe", NULL) < 0)
                {
                        perror("execl");
                        exit(2);
                }
        }
        else
        {
                while(1)
                {
                        char answer;
                        char menu[MENU_SIZE];

                        int rfd, sfd;


                        printf("[부모] 주문하시겠습니까? (y/n) : ");
                        scanf("%c", &answer);
                        getchar();
                        printf("[부모] 메뉴를 입력해주세요. (문자열) : ");
                        fgets(menu, sizeof(menu), stdin);
                        menu[strlen(menu)-1] = '\0';
                        printf("[부모] %s주문을 주방에 전달합니다.", menu);
                        if((answer == 'y') || (answer == 'Y'))
                        {
                                if((rfd = open(fifo2, O_RDONLY)) < 0)
                                {
                                        fprintf(stderr, "Error in open %s\n", fifo2);
                                        exit(4);
                                }

                                if((sfd = open(fifo1, O_WRONLY)) < 0)
                                {
                                        fprintf(stderr, "Error in open %s\n", fifo1);
                                        exit(4);
                                }
                                write(sfd, menu, sizeof(menu));
                                getchar();
                                close(rfd);
                                close(sfd);
                                wait();
                        }
                }
        }
}
