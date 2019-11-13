#include<stdio.h>
  
#include"mystruct.h"
#include"append.h"

int main(int argc, char *argv[])
{
        if(argc!=7)
        {
                printf("이 프로그램은 파일명,학번,이름,국어점수,영어점수,수학점수를 인자로 받아야합니다\n");
                printf(" Usage: %s filename (학번) (이름) (국어) (영어) (수학)\n",argv[0]);
                exit(2);
        }
        char *file;
        file=argv[1];
        append(file,atoi(argv[2]),argv[3],atoi(argv[4]),atoi(argv[5]),atoi(argv[6]));
        return 0;
}
