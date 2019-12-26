#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define TIME_FOR_PIZZA 10
#define TIME_FOR_CHICKEN 15

typedef struct in_progress {
        int time;
        struct in_progress *next;
}in_progress_t;

in_progress_t *header = NULL;
void sigusr1_handler(int signo);

void alrm_handler(int signo)
{
        in_progress_t *tmp;
        tmp = header->next;
        int all_time = 0;
        while(tmp != NULL)
        {
                all_time = all_time + tmp->time;
                printf("\n[자식] 현재 진행중 요리 남은시간 :  %d\n", all_time);
                tmp = tmp->next;
        }
        free(tmp);

        tmp = header;
        if(header->next)
        {
                header = header->next;
                alarm(header->time);
        }

        else
        {
                header = NULL;
                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = SIG_DFL;
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }

                act.sa_handler = SIG_IGN;
                if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction eroor");
                        exit(3);
                }
        }

        kill(getppid(), SIGUSR1);
        free(tmp);
}

void sigusr1_handler(int signo)
{
        in_progress_t *tmp;
        in_progress_t *prev;
        in_progress_t *new;

        printf("\n[자식] 피자주문 도착\n");

        new = malloc(sizeof(in_progress_t));
        new->time = TIME_FOR_PIZZA;
        new->next = NULL;

        if(header == NULL)
        {
                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = SIG_IGN;
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }

                act.sa_handler = alrm_handler;
                if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }
                header = new;
        }
        else
        {
                header->time = alarm(0);

                for(tmp = header; tmp; prev = tmp, tmp = tmp->next)
                {
                new->time = new->time - tmp->time;
                }
                if(new->time <= 0)
                {
                        new->time = 1;
                }
                prev->next = new;
        }

        printf("\n");
        in_progress_t *left_time;
        int all_time = 0;
        left_time = header;
        while(left_time != NULL)
        {
                all_time = all_time + left_time->time;
                printf("[자식] 남은요리시간 : %d\n", all_time);
                left_time = left_time->next;
        }
        alarm(header->time);
}

void sigusr2_handler(int signo)
{
        in_progress_t *tmp;
        in_progress_t *prev;
        in_progress_t *new;

        printf("\n[자식] 치킨주문 도착\n");

        new = malloc(sizeof(in_progress_t));
        new->time = TIME_FOR_CHICKEN;
        new->next = NULL;

        if(header == NULL)
        {
                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = SIG_IGN;
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }

                act.sa_handler = alrm_handler;
                if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaction error");
                        exit(3);
                }
                header = new;
        }
        else
        {
                header->time = alarm(0);

                for(tmp = header; tmp; prev = tmp, tmp = tmp->next)
                {
                        new->time = new->time - tmp->time;
                }
                if(new->time <= 0)
                {
                        new->time = 1;
                }
                prev->next = new;
        }

        printf("\n");
        in_progress_t *left_time;
        int all_time = 0;
        left_time = header;
        while(left_time != NULL)
        {
                all_time = all_time + left_time->time;
                printf("[자식] 남은요리시간 : %d\n", all_time);
                left_time = left_time->next;
        }

        alarm(header->time);
}

int main(void)
{
        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        act.sa_handler = sigusr1_handler;
        if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction error");
                exit(3);
        }

        act.sa_handler = sigusr2_handler;
        if(sigaction(SIGUSR2, &act, (struct sigaction *)NULL) < 0)
        {
        perror("sigaction error");
                exit(3);
        }

        while(1)
        {
                sleep(999);
        }
}
