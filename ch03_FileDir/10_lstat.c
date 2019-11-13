#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
        if(argc!=4)
        {
                fprintf(stderr, "usage : %s org_file lnk_file sym_lnk_file\n", argv[0]);
                exit(1);
        }

        char *org_file = argv[1];
        char *lnk_file = argv[2];
        char *sym_lnk_file = argv[3];

        struct stat buf;

        printf("1. stat : %s ---\n", org_file);
        if(stat(org_file, &buf) !=0)
        {
                perror("stat");
        }
        else
        {
                printf("%s : Link Count = %d\n", org_file, (int)buf.st_nlink);
                printf("%s : Inode = %d\n", org_file, (int)buf.st_ino);
        }

        printf("2. stat : %s ---\n", lnk_file);
        if(stat(lnk_file, &buf) !=0)
        {
                perror("stat");
        }
        else
        {
                printf("%s : Link Count = %d\n", lnk_file, (int)buf.st_nlink);
                printf("%s : Inode = %d\n", lnk_file, (int)buf.st_ino);
        }

        printf("3. stat : %s ---\n", sym_lnk_file);
        if(lstat(sym_lnk_file, &buf) !=0)
        {
                perror("stat");
        }
        else
        {
                printf("%s : Link Count = %d\n", sym_lnk_file, (int)buf.st_nlink);
                printf("%s : Inode = %d\n", sym_lnk_file, (int)buf.st_ino);
        }
        return 0;
}
