#include<stdio.h>
  
#include"mystruct.h"
#include"process.h"

int main(int argc, char *argv[])
{
        if(argc<2)
        {
                printf("파일 1개와 같이 사용하세요.\n사용예 : %s data.dat",argv[0]);
                exit(1);
        }
        char *file;
        file=argv[1];
        process(file);

        return 0;
}
