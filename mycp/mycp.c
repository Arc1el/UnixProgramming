#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#define BUF_SIZE 512

int main(int argc, char *argv[])
{
        int fd1,fd2,rd_cnt;
        char buf[BUF_SIZE];


        if(argc<3)
        {
                fprintf(stderr,"반드시 파일이름 2개와 함께 사용되어야합니다.\n실행예 : %s abc.c def.c\n",argv[0]);
                exit(1);
        }

        fd1  = open(argv[1], O_RDONLY);
        if(fd1<0)
        {
                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[1]);
                if(errno==ENOENT)
                        printf("복사할 소스파일(%s)이 존재하지 않음.\n",argv[1]);
                exit(2);
        }

        fd2  = open(argv[2], O_CREAT | O_RDWR | O_EXCL ,0644);
        if(fd2<0)
        {
                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[2]);
                if(errno==EEXIST)
                        printf("복사할 대상파일(%s)이 이미 존재함.\n",argv[2]);
                exit(2);
        }


        while((rd_cnt=read(fd1,buf,BUF_SIZE))>0)
        {
                if(write(fd2,buf,rd_cnt)!=rd_cnt)
                {
                        perror("파일을 쓰는중 오류발생\n");
                        exit(3);
                }
        }
        if(rd_cnt<0)
        {
                perror("파일을 읽는중 오류 발생\n");
                exit(3);
        }

        close(fd1);
        close(fd2);

        return 0;
}
