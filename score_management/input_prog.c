#include<stdio.h>
  
#include"mystruct.h"
#include"input.h"

int main(int argc, char *argv[])
{
        if(argc<2)
        {
                printf("���������� 1���� ���� ����ϼ���.\n��뿹 : %s data.dat",argv[0]);
                exit(1);
        }
        char *file;
        file=argv[1];

        input(file);

        return 0;
}
