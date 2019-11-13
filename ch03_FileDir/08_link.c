#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if(argc!=3)
        {
                fprintf(stderr, "Usage : %s org_file lnk_file\n", argv[0]);
                exit(1);
        }

        char *org_filename=argv[1];
        char *lnk_filename=argv[2];

        struct stat buf;
        if (stat(org_filename, &buf) != 0)
        {
                perror("stat");
                exit(2);
        }
        printf("Before Link Count = %d\n", (int)buf.st_nlink);

        if(link(org_filename, lnk_filename) !=0)
        {
                perror("link");
                exit(3);
        }
        if(stat(lnk_filename, &buf) !=0)
        {
                perror("stat");
                exit(4);
        }
        printf("After Link Count = %d\n", (int)buf.st_nlink);

        return 0;
}