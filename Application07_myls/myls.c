#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char*argv[])
{
        if(argc!=2)
        {
                fprintf(stderr,"사용법 : %s (디렉토리명)\n",argv[0]);
                exit(1);
        }
        char *dirnam=argv[1];
        DIR *dp;
        int count=0;

        if((dp=opendir(dirnam))==NULL)
        {
                perror("디렉토리 열기실패");
                exit(2);
        }
        seekdir(dp,6);

        struct dirent *dent;

        while((dent=readdir(dp)))
        {
                printf("%12s ",dent->d_name);
                count++;
                if(count%7==0)
                {
                        printf("\n");
                }
        }
        printf("\n");
        closedir(dp);
        return 0;
}
