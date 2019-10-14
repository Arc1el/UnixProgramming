#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
        int opn,rd,i;
        int line=1;
        char buf[100];

        if(argc<2)
        {
                fprintf(stderr,"이 프로그램은 1개의 파일명을 명령행인자로 받아야합니다.\n");
                exit(1);
        }

        if(argc>2)
        {
                fprintf(stderr,"이 프로그램은 오직 1개의 파일명만을 명령행인자로 받을수있습니다.\n");
                exit(1);
        }

        opn = open(argv[1], O_RDONLY);
        if(opn==-1)
        {
                perror("파일을 여는중 오류 발생");
                exit(1);
        }

        printf("%2d : ", line++);

        while((rd=read(opn,buf,100))>0)
        {
                for(i=0;i<rd;i++)
                {
                        printf("%c", buf[i]);
                        if(buf[i]=='\n')
                        {
                                printf("%2d : ", line++);
                        }
                }
        }

        if(rd==-1)
        {
                perror("파일을 읽는중 오류 발생");
                exit(1);
        }

        printf("파일을 모두 불러왔습니다.\n");
        close(opn);

        return 0;
}
