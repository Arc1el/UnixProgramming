#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
        if(argc!=3)
        {
                fprintf(stderr, "Usage : %s dir1 dir2\n", argv[0]);
                exit(1);
        }

        char *dir_name1 = argv[1];
        char *dir_name2 = argv[2];

        if (mkdir(dir_name1, 0755) == -1)
        {
                perror("mkdir");
                exit(2);
        }
        if (rename(dir_name1,dir_name2) == -1)
        {
                perror("rename");
                exit(3);
        }
        if (rmdir(dir_name2) == -1)
        {
                perror("rmdir");
                exit(4);
        }

        return 0;
}
