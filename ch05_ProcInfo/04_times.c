#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/times.h>
#include<limits.h>

int main()
{
        struct tms mytms;
        clock_t t1;

        if((t1=times(&mytms))==-1)
        {
                perror("times 1");
                exit(1);
        }
        printf("T1 : %ld \n", t1);
        printf("User TICKS : %ld TICKS\n", mytms.tms_utime);
        printf("System Ticks : %ld TICKS\n\n", mytms.tms_stime);

        int i;
        time_t t;
        for(i=0; i<100000000; i++)
        {
                time(&t);
        }

        clock_t t2;
        if((t2=times(&mytms))==-1)
        {
                perror("times 2");
                exit(1);
        }

        printf("T2 : %ld \n", t2);
        printf("User TICKS : %ld TICKS\n",mytms.tms_utime);
        printf("System TICKS : %ld TICKS\n\n", mytms.tms_stime);

        int clk_sec;
        clk_sec=sysconf(_SC_CLK_TCK);

        printf("T1 : %ld \tT2 : %ld\t TICKS_PER_SEC : %ld\n", t1,t2,clk_sec);
        printf("Real time : %lf sec\n", (double)(t2-t1)/clk_sec);
        printf("User time : %lf sec\n", (double)mytms.tms_utime/clk_sec);
        printf("System time : %lf sec\n", (double)mytms.tms_stime/clk_sec);

        return 0;
}