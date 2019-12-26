#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

#define MODE_SIZE       9
#define MODE_STR_SIZE   10

static short octarray[MODE_SIZE]={0400,0200,0100,0040,0020,0010,0004,0002,0001};
static char perms[MODE_STR_SIZE]="rwxrwxrwx";

void normal_print();
void detail_print();

int main(int argc, char*argv[])
{
        if(argc<2)
        {
                fprintf(stderr,"사용법 : %s (디렉토리명)\n세부정보 %s -l (디렉토리명)\n", argv[0], argv[0]);
                exit(1);
        }

        char *dirnam;
        int opt;
        while((opt = getopt(argc, argv, "l")) != -1)
        { //옵션 주어질경우 진행
                if(opt == 'l' && argc == 3)
                {
                        dirnam = argv[2];
                        detail_print(dirnam);
                        exit(0);
                }
                else
                {
                        fprintf(stderr,"잘못된 옵션 사용함\n사용법 : %s (디렉토리명)\n세부정보 %s -l (디렉토리명)\n"
                                        ,argv[0], argv[0]);
                        exit(6);
                }
        }
        //옵션 주어지지 않을경우 진행
        dirnam = argv[1];
        normal_print(dirnam);
        return 0;
}

void normal_print(char *dirnam)
{
        DIR *dp;
        if((dp=opendir(dirnam)) == NULL)
        {
                perror("디렉토리 열기실패");
                exit(2);
        }

        struct dirent *dent;
        int count = 0;
        while((dent = readdir(dp)))
        {
                printf("%12s ", dent->d_name);
                count++;
                if(count%7 == 0)
                {
                        printf("\n");
                }
        }
        closedir(dp);
        printf("\n");
}

void detail_print(char *dirnam)
{
        DIR *dp;
        if((dp=opendir(dirnam)) == NULL)
        {
                perror("디렉토리 열기실패");
                exit(3);
        }

        printf("%s%s %s    %s   %11s    %10s  %5s  %s  %s\n","종류및","권한","링크","inode값",
                        "소유자","소유그룹","크기","마지막수정일","파일명");

        struct stat buf;
        struct dirent *dent;
        while((dent = readdir(dp)))
        {
                if(lstat(dent->d_name, &buf) < 0)
                {
                        perror("lstat");
                        exit(4);
                }

                int i;
                char mode_str[MODE_STR_SIZE];
                for(i=0; i<MODE_SIZE; i++)
                {
                        if(buf.st_mode & octarray[i])
                        {
                                mode_str[i] = perms[i];
                        }
                        else
                        {
                                mode_str[i] = '-';
                        }
                }
                mode_str[MODE_STR_SIZE -1] = '\0';

                char file_type;
                if(S_ISFIFO(buf.st_mode)) file_type = 'p';
                if(S_ISDIR(buf.st_mode)) file_type = 'd';
                if(S_ISREG(buf.st_mode)) file_type = '-';
                if(S_ISLNK(buf.st_mode)) file_type = 'l';

                struct passwd *pw;
                struct group *grp;
                pw = getpwuid(buf.st_uid);
                grp = getgrgid(buf.st_gid);

                struct tm time;
                time = *localtime(&(buf.st_mtime));

                char time_buf[BUFSIZ];
                strftime(time_buf, sizeof(time_buf), "%m월 %d %H:%M", &time);

                printf("%c%s. %2o %12d %10s %10s %5d %s %s",
                                file_type, mode_str, (unsigned int)buf.st_nlink, (int)buf.st_ino, pw->pw_name,
                                grp->gr_name, (int)buf.st_size, time_buf, dent->d_name);

                if(S_ISLNK(buf.st_mode))
                {
                        char lnk_src[BUFSIZ];
                        int lnk;
                        lnk = readlink(dent->d_name, lnk_src, BUFSIZ);
                        if(lnk == -1)
                        {
                                perror("readlink");
                                exit(5);
                        }
                        lnk_src[lnk] = '\0';
                        printf(" -> %s\n", lnk_src);
                }
                else
                {
                        printf("\n");
                }
        }
        closedir(dp);
}
