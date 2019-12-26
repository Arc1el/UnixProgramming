#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
        extern char *optarg;
        int opt;

        opt=getopt(argc,argv,"au:h");

        if(argc<2)
        {
                fprintf(stderr,"1개이상의 명령행인자와 함께  사용하십시오.\n");
                printf("-a : ""Welcome to UNIX Sysytem Programming!""을 출력합니다.\n");
                printf("-u 인자: ""Nice to meet [인자]""를 출력합니다.\n");
                printf("-h : 사용가능한 옵션목록 출력합니다.\n");
                exit(1);
        }

        switch (opt)
        {
                case 'a':
                        if(argc>2)
                        {
                                fprintf(stderr,"여러옵션과 사용이 불가능합니다.\n");
                                exit(1);
                        }
                        printf("""Welcome To UNIX System Programming!""\n");
                        break;
                case 'u':
                        if(argc>3)
                        {
                                fprintf(stderr,"여러옵션과 사용이 불가능합니다.\n");
                                exit(1);
                        }
                        printf("""Nice to meet %s""\n",optarg);
                        break;
                case 'h':
                if(argc>2)
                        {
                                fprintf(stderr,"여러옵션과 사용이 불가능합니다.\n");
                                exit(1);
                        }
                        printf("-a : ""Welcome to UNIX Sysytem Programming!""을 출력합니다.\n");
                        printf("-u 인자: ""Nice to meet [인자]""를 출력합니다.\n");
                        printf("-h : 사용가능한 옵션목록 출력합니다.\n");
                        break;

                default :
                        printf("잘못된 옵션을 사용하였습니다. h옵션으로 사용법을 숙지하세요.\n");
                        break;

        }
        return 0;
}
