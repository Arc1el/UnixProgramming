#include<stdio.h>
  
#include"mystruct.h"
#include"append.h"

int main(int argc, char *argv[])
{
        if(argc!=7)
        {
                printf("�� ���α׷��� ���ϸ�,�й�,�̸�,��������,��������,���������� ���ڷ� �޾ƾ��մϴ�\n");
                printf(" Usage: %s filename (�й�) (�̸�) (����) (����) (����)\n",argv[0]);
                exit(2);
        }
        char *file;
        file=argv[1];
        append(file,atoi(argv[2]),argv[3],atoi(argv[4]),atoi(argv[5]),atoi(argv[6]));
        return 0;
}
