#include<time.h>
#include<stdio.h>

char *output[] = {
        "%x %X",
        "%G 년 %m 월 %d 일 %U 주 %H:%M",
        "%r"
};

int main(void)
{
        struct tm *tm;
        int n;
        time_t t;
        char buf[BUFSIZ];

        time(&t);
        tm=localtime(&t);

        for (n=0; n<3; n++)
        {
                strftime(buf,sizeof(buf),output[n], tm);
                printf("%s = %s\n", output[n], buf);
        }
        return 0;

}
