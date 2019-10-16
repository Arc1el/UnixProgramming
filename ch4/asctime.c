#include<time.h>
#include<stdio.h>

int main(void)
{
        time_t t;
        time(&t);

        struct tm *tm;
        tm=localtime(&t);

        printf("Time(sec) : %d\n", (int)t);
        printf("Time(date) : %s\n", asctime(tm));

        return 0;
}
