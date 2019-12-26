#include<stdio.h>
  
#include"mystruct.h"
void process(char *file)
{

        score stu;
        FILE *fp;
        printf("성적 처리 프로그램입니다.\n");
        fp=fopen(file,"rb");
        if(fp==NULL)
        {
                perror("파일을 여는데 오류가 발생하였습니다.");
                exit(1);
        }
        int n,count=0,total_korean=0,total_english=0,total_math=0,total=0;
        float avg,total_avg,korean_avg,english_avg,math_avg;

        while ((n=fread(&stu,sizeof(score),1,fp))>0)
        {
                count++;
                total_korean=total_korean+stu.korean;
                total_english=total_english+stu.english;
                total_math=total_math+stu.math;
                avg=avg+stu.avg;
        }

        total=total_korean+total_english+total_math;
        total_avg=avg/count;
        korean_avg=total_korean/count;
        english_avg=total_english/count;
        math_avg=total_math/count;

        printf("%5s  %5s  %5s  %5s  %5s  %5s  %5s  %5s\n","국어총점","국어평균","영어총점","영어평균","수학총점","수
학평균","전체총점","전체평균");
        printf("  %5d     %.2f     %5d     %.2f     %5d     %.2f     %5d     %.2f\n",total_korean,korean_avg,total_english,english_avg,total_math,math_avg,total, total_avg);

        fclose(fp);
}
