#include<stdio.h>
#include<string.h>
#include"mystruct.h"

void input(char *file)
{
        score stu;
        printf("�����Է����α׷��Դϴ�.\n");
        FILE *fp;
        fp=fopen(file,"wb+");
        if(fp==NULL)
        {
                perror("������ ���µ� ������ �߻��Ͽ����ϴ�.");
                exit(1);
        }
        while(1)
        {
                memset(&stu,0,sizeof(stu));
                printf("�й��� �Է��ϼ���(����0) : ");
                scanf("%d",&stu.id);
                if(stu.id==0)
                {
                        printf("0�� �Է��Ͽ� �����մϴ�.\n");
                        break;
                }
                __fpurge(stdin);
                printf("�̸��� �Է��ϼ��� : ");
                fgets(stu.name,sizeof(stu.name),stdin);
                stu.name[strlen(stu.name)-1]='\0';
                __fpurge(stdin);
                printf("���������� �Է��ϼ��� : ");
                scanf("%d",&stu.korean);
                __fpurge(stdin);
                printf("���������� �Է��ϼ��� : ");
                scanf("%d",&stu.english);
                __fpurge(stdin);
                printf("���������� �Է��ϼ��� : ");
                scanf("%d",&stu.math);
                __fpurge(stdin);
                stu.all= stu.korean + stu.english + stu.math;
                stu.avg= stu.all/3;

                fwrite(&stu,sizeof(score),1,fp);
        }
        fclose(fp);
}
