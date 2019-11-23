#include<stdio.h>
#include<stdlib.h>

int main(void)
{
        FILE *fp;
        char buf[BUFSIZ];

        fp = popen("date", "r");
        if(fp == NULL)
        {
                fprintf(stderr, "popen failed\n");
                exit(1);
        }

        if(fgets(buf, BUFSIZ, fp) == NULL)
        {
                fprintf(stderr, "No data form pipe!\n");
                exit(1);
        }

        printf("line : %s\n", buf);
        pclose(fp);

        return 0;
}
