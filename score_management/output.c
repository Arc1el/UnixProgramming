#include<stdio.h>
#include"mystruct.h"
void output(char *file)
{
        score stu;
        FILE *fp;
        int n;
        printf("���� ��� ���α׷��Դϴ�.\n");
        fp=fopen(file,"rb");
        if(fp==NULL)
        {
                perror("������ ���µ� ������ �߻��Ͽ����ϴ�.");
                exit(1);
        }
        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����","����","���");
        while ((n=fread(&stu,sizeof(score),1,fp))>0)
        {
                printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
        }
        fclose(fp);
}