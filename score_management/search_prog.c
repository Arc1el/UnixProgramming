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
                printf("�ɼ� �ϳ��� �䱸�� arguments�� ���� ����ϼ���.\n");
                printf(" Usage: %s (option) (required arguments)\n",file);
                printf(" -n (�̸�) �̸����� ���� �˻�\n");
                printf(" -i (�й�) �й����� ���� �˻�\n");
                printf(" -o ���� ���� �����л� ��� (�����ΰ�� �������л� ���)\n");
                printf(" -s ���� ���� �����л� ��� (�����ΰ�� ����л� ���)\n");
                exit(1);
        }
        extern char *optarg;
        int search_opt;

        search_opt=getopt(argc,argv,"n:i:os");
        search(file,search_opt,optarg);

        return 0;
}
