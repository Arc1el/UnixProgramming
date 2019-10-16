#include<stdio.h>
#include<sys/types.h>
#include<time.h>

int main(void)
{
        time_t tt;

        time(&tt);
        printf("Time(sec) : %d\n", (int)tt);

        return 0;
}
