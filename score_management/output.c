#include<stdio.h>
#include"mystruct.h"
void output(char *file)
{
        score stu;
        FILE *fp;
        int n;
        printf("성적 출력 프로그램입니다.\n");
        fp=fopen(file,"rb");
        if(fp==NULL)
        {
                perror("파일을 여는데 오류가 발생하였습니다.");
                exit(1);
        }
        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","학번","이름","국어","영어","수학","총점","평균");
        while ((n=fread(&stu,sizeof(score),1,fp))>0)
        {
                printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
        }
        fclose(fp);
}