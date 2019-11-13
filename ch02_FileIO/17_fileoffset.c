#include<stdlib.h>
#include<stdio.h>

int main(void)
{
        FILE *fp;
        int n;
        long cur;
        char buf[BUFSIZ];

        if((fp = fopen("unix.txt","r"))==NULL)
        {
                perror("fopen:unix.txt");
                exit(1);
        }

        n=fread(buf,sizeof(char),4,fp);
        buf[n]='\0';
        printf("-- Read Str=%s\n", buf);

        cur=ftell(fp);
        printf("Offset cur=%d\n", (int)cur);

        fseek(fp,3,SEEK_CUR);
        cur=ftell(fp);
        printf("Offset cur=%d\n", (int)cur);

        n=fread(buf,sizeof(char),6,fp);
        buf[n]='\0';
        printf("-- Read Str=%s\n", buf);

        cur=ftell(fp);
        printf("Offset cur=%d\n", (int)cur);

        fclose(fp);

        return 0;
}
