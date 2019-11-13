#include<stdio.h>
#include<string.h>

#include"mystruct.h"

void search(char *file,int search_opt,char *optarg)
{
        score stu;
        int n,return_strcmp,search_id,exist_check=0;
        int best_stu;
        float tmp;
        printf("���� Ž�� ���α׷��Դϴ�\n");
        FILE *fp;
        char search_name[sizeof(stu.name)];
        fp=fopen(file,"rb");
        if(fp==NULL)
        {
                perror("������ ���µ� ������ �߻��Ͽ����ϴ�.");
                exit(1);
        }
        switch(search_opt)
        {
                case 'n':
                        memset(search_name,0,sizeof(search_name));
                        strncpy(search_name,optarg,sizeof(search_name));
                        printf("�̸����� ������ ã���ϴ�. (�̸�: %s)\n",search_name);
                        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����","����","���");
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                return_strcmp=strcmp(stu.name,search_name);
                                if(return_strcmp==0)
                                {
                                        printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
                                        exist_check++;
                                }
                        }
                        if(exist_check==0)
                        {
                                printf("�ش��л��� ������ �����ϴ�.\n");
                                exit(3);
                        }
                        fclose(fp);
                        break;
                case 'i':
                        search_id=atoi(optarg);
                        printf("�й����� ������ ã���ϴ�. (�й�: %s)\n",optarg);
                        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����","����","���");
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                if(stu.id==search_id)
                                {
                                        printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
                                        exist_check++;
                                }
                        }
                        if(exist_check==0)
                        {
                                printf("�ش��л��� ������ �����ϴ�.\n");
                                exit(3);
                        }
                        fclose(fp);
                        break;
                case 'o':
                        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����","����","���");
                        tmp=0;
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                if(stu.avg>=tmp)
                                {
                                        best_stu=stu.id;
                                }
                        }
                        fseek(fp,0L,SEEK_SET);
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                if(best_stu==stu.id)
                                {
                                        printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
                                }
                        }
                        fclose(fp);
                        break;
                case 's':
                        printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n","�й�","�̸�","����","����","����","����","���");
                        tmp=0;
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                if(stu.avg>=tmp)
                                {
                                        tmp=stu.avg;
                                }
                                else if(stu.avg<tmp)
                                {
                                        tmp=tmp;
                                }
                        }
                        fseek(fp,0L,SEEK_SET);
                        while ((n=fread(&stu,sizeof(score),1,fp))>0)
                        {
                                if(stu.avg==tmp)
                                {
                                        printf("%8d%7s\t%7d\t%7d\t%7d\t%7d\t%.2f\n",stu.id, stu.name, stu.korean, stu.english, stu.math, stu.all, stu.avg);
                                }
                        }
                        fclose(fp);
                        break;
                default :
                        printf("�ƹ��ɼǵ� �������� �ʾ� �����մϴ�.\n");
                        fclose(fp);
                        break;
        }
}
