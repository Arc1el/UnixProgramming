#include<stdio.h>
#include"mystruct.h"

void append(char *file, int id, char *name,int korean, int english, int math)
{
        printf("성적 추가 프로그램입니다.\n");
        printf("추가할 학생데이터는 다음과 같습니다.\n");
        printf("%8s\t%8s\t%8s\t%8s\t%8s\n","학번","이름","국어","영어","수학");
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
                perror("파일을 여는데 오류가 발생하였습니다.");
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
