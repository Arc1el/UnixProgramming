#include<stdio.h>
  
#include"mystruct.h"
#include"search.h"

int main(int argc, char *argv[])
{
        extern int optind;
        char *file;
        file=argv[1];
        if(argc-optind<2)
        {
                printf("옵션 하나와 요구된 arguments를 같이 사용하세요.\n");
                printf(" Usage: %s (option) (required arguments)\n",file);
                printf(" -n (이름) 이름으로 성적 검색\n");
                printf(" -i (학번) 학번으로 성적 검색\n");
                printf(" -o 가장 성적 좋은학생 출력 (동점인경우 마지막학생 출력)\n");
                printf(" -s 가장 성적 좋은학생 출력 (동점인경우 모든학생 출력)\n");
                exit(1);
        }
        extern char *optarg;
        int search_opt;

        search_opt=getopt(argc,argv,"n:i:os");
        search(file,search_opt,optarg);

        return 0;
}
