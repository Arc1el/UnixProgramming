#include<time.h>
#include<stdio.h>

int main(void)
{
        time_t t;

        time(&t);
        printf("Current Time(sec) : %d\n", (int)t);

        struct tm tm;
        tm.tm_year = 118;
        tm.tm_mon = 9;
        tm.tm_mday = 31;
        tm.tm_hour = 12;
        tm.tm_min = 30;
        tm.tm_sec = 0;

        t=mktime(&tm);
        printf("2019/10/14 15:000:00 Time(sec) : %d\n", (int)t);

        return 0;
}
