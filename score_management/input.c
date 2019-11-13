#include<stdio.h>
#include<string.h>
#include"mystruct.h"

void input(char *file)
{
        score stu;
        printf("성적입력프로그램입니다.\n");
        FILE *fp;
        fp=fopen(file,"wb+");
        if(fp==NULL)
        {
                perror("파일을 여는데 오류가 발생하였습니다.");
                exit(1);
        }
        while(1)
        {
                memset(&stu,0,sizeof(stu));
                printf("학번을 입력하세요(종료0) : ");
                scanf("%d",&stu.id);
                if(stu.id==0)
                {
                        printf("0을 입력하여 종료합니다.\n");
                        break;
                }
                __fpurge(stdin);
                printf("이름을 입력하세요 : ");
                fgets(stu.name,sizeof(stu.name),stdin);
                stu.name[strlen(stu.name)-1]='\0';
                __fpurge(stdin);
                printf("국어점수를 입력하세요 : ");
                scanf("%d",&stu.korean);
                __fpurge(stdin);
                printf("영어점수를 입력하세요 : ");
                scanf("%d",&stu.english);
                __fpurge(stdin);
                printf("수학점수를 입력하세요 : ");
                scanf("%d",&stu.math);
                __fpurge(stdin);
                stu.all= stu.korean + stu.english + stu.math;
                stu.avg= stu.all/3;

                fwrite(&stu,sizeof(score),1,fp);
        }
        fclose(fp);
}
