#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

#define MODE_SIZE       9
#define MODE_STR_SIZE   10

static short octarray[MODE_SIZE]={0400,0200,0100,0040,0020,0010,0004,0002,0001};

static char perms[MODE_STR_SIZE]="rwxrwxrwx";

int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                fprintf(stderr,"Usage: %s filename\n", argv[0]);
                exit(1);
        }

        char *filename = argv[1];
        printf("파일명 : %s\n",argv[1]);

        int kind;
        struct stat stat_buf;

        if (stat(filename,&stat_buf)<0)
        {
                perror("stat");
                exit(2);
        }

        kind=stat_buf.st_mode & S_IFMT;
        printf("파일종류 : ");
        switch(kind)
        {
                case S_IFIFO:
                        printf("FIFO파일\n");
                        break;
                case S_IFDIR:
                        printf("디렉토리파일\n");
                        break;
                case S_IFREG:
                        printf("일반파일\n");
                        break;
        }

        char mode_str[MODE_STR_SIZE];
        int i;
        for(i=0; i<MODE_SIZE; i++)
        {
                if(stat_buf.st_mode & octarray[i])
                {
                        mode_str[i]=perms[i];
                }
                else
                {
                        mode_str[i]='-';
                }
        }
        mode_str[MODE_STR_SIZE -1]='\0';
        printf("접근 권한 : %s\n", mode_str);

        if(stat(argv[1], &stat_buf)==0)
        {
                printf("UID : %d\n",(int)stat_buf.st_uid);
                printf("파일 수정시간 : %d\n",(int)stat_buf.st_mtime);
        }
        else
        {
                perror("stat");
        }


        return 0;
}
