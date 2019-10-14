#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

int main(int argc, char *argv[])
{
        int cp1,cp2,rw;
        int opt;
        char buf[100];

        if(argv[1][1]=='h')
        {
                fprintf(stderr,"-x : 복사할파일이 존재하는경우 오류메세지 출력후 종료\n-t : 복사할 파일이 존재하는 경우 무조건 지우고 복사\n-y : 복사할 파일이 존재하는경우 사용자에게 메시지를 출력하고,사용자가 y를 답하는 경우 지우고 복사, 그렇지 않은경우 종료\n\n옵션이 지정되지 않으면 옵션x로 동작합니다.\n");
                exit(1);
        }
        else if(argc=3)
        {
                if(argv[1][1]=='x')
                {
                        fprintf(stderr,"대상파일명을 입력하세요\n");
                        exit(1);
                }
                else if(argv[1][1]=='t')
                {
                        fprintf(stderr,"대상파일명을 입력하세요\n");
                        exit(1);
                }
                else if(argv[1][1]=='y')
                {
                        fprintf(stderr,"대상파일명을 입력하세요\n");
                        exit(1);
                }
        }

        opt=getopt(argc,argv,"xty");

        switch(opt)
        {
                case 'x' :
                        cp1  = open(argv[3], O_RDONLY);
                        if(cp1==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[3]);
                                if(errno==2)
                                        printf("복사할 소스파일(%s)이 존재하지 않음.\n",argv[3]);
                                exit(1);
                        }

                        cp2 = open(argv[4], O_CREAT | O_RDWR | O_EXCL ,0644);
                        if(cp2==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[4]);
                                if(errno==17)
                                        printf("복사할 대상파일(%s)이 이미 존재함.\n",argv[4]);
                                exit(1);
                        }


                        while((rw=read(cp1,buf,100))>0)
                        {
                                if(write(cp2,buf,rw)!=rw)
                                        perror("파일을 쓰는중 오류 발생\n"); exit(1);
                        }
                        if(rw==-1)
                        {
                                perror("파일을 읽는중 오류 발생\n");
                                exit(1);
                        }
                        break;
                case 't' :
                        cp1  = open(argv[3], O_RDONLY);
                        if(cp1==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[3]);
                                if(errno==2)
                                        printf("복사할 소스파일(%s)이 존재하지 않음.\n",argv[3]);
                                exit(1);
                        }

                        cp2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC  ,0644);
                        if(cp2==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[4]);
                                exit(1);
                        }


                        while((rw=read(cp1,buf,100))>0)
                        {
                                if(write(cp2,buf,rw)!=rw)
                                        perror("파일을 쓰는중 오류 발생\n"); exit(1);
                        }
                        if(rw==-1)
                        {
                                perror("파일을 읽는중 오류 발생\n");
                                exit(1);
                        }
                        break;
                case 'y' :
                        cp1  = open(argv[3], O_RDONLY);
                        if(cp1==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[3]);
                                if(errno==2)
                                        printf("복사할 소스파일(%s)이 존재하지 않음.\n",argv[3]);
                                exit(1);
                        }

                        cp2 = open(argv[4], O_CREAT | O_RDWR | O_EXCL ,0644);
                        if(cp2==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[4]);
                                if(errno==17)
                                        printf("복사할 대상파일(%s)이 이미 존재함.\n",argv[4]);
                                exit(1);
                        }


                        while((rw=read(cp1,buf,100))>0)
                        {
                                if(write(cp2,buf,rw)!=rw)
                                        perror("파일을 쓰는중 오류 발생\n"); exit(1);
                        }
                        if(rw==-1)
                        {
                                perror("파일을 읽는중 오류 발생\n");
                                exit(1);
                        }
                        break;
                default :
                        cp1  = open(argv[2], O_RDONLY);
                        if(cp1==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[2]);
                                if(errno==2)
                                        printf("복사할 소스파일(%s)이 존재하지 않음.\n",argv[2]);
                                exit(1);
                        }

                        cp2 = open(argv[3], O_CREAT | O_RDWR | O_EXCL ,0644);
                        if(cp2==-1)
                        {
                                fprintf(stderr,"%s를 여는데 오류 발생\n",argv[3]);
                                if(errno==17)
                                        printf("복사할 대상파일(%s)이 이미 존재함.\n",argv[3]);
                                exit(1);
                        }


                        while((rw=read(cp1,buf,100))>0)
                        {
                                if(write(cp2,buf,rw)!=rw)
                                        perror("파일을 쓰는중 오류 발생\n"); exit(1);
                        }
                        if(rw==-1)
                        {
                                perror("파일을 읽는중 오류 발생\n");
                                exit(1);
                        }
        }
        close(cp1);
        close(cp2);
        close(rw);
        return 0;
}
