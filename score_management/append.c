#include<stdio.h>
#include"mystruct.h"

void append(char *file, int id, char *name,int korean, int english, int math)
{
        printf("���� �߰� ���α׷��Դϴ�.\n");
        printf("�߰��� �л������ʹ� ������ �����ϴ�.\n");
        printf("%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����");
        printf("%8d%7s\t%7d\t%7d\t%7d\n",id,name,korean,english,math);

        int all;
        all=korean+english+math;
        float avg;
        avg=all/3;
        int i;
        score stu;
        FILE *fp;
        fp=fopen(file,"ab");
        if(fp==NULL)
        {
                perror("������ ���µ� ������ �߻��Ͽ����ϴ�.");
                exit(1);
        }
        stu.id=id;
        for(i=0; i<=sizeof(stu.name); i++)
        {
                stu.name[i]=name[i];
        }
        stu.korean=korean;
        stu.english=english;
        stu.math=math;
        stu.all=all;
        stu.avg=avg;
        fwrite(&stu,sizeof(score),1,fp);

        fclose(fp);
}
