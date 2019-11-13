#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                fprintf(stderr, "Usage : %s dir_name\n", argv[0]);
                exit(1);
        }
        char *dir_name=argv[1];

        DIR *dp;
        if ((dp=opendir(dir_name)) == NULL)
        {
                perror("opendir");
                exit(2);
        }

        struct dirent *dent;
        while ((dent=readdir(dp)))
        {
                printf("Name : %s  ", dent->d_name);
                printf("Inode : %d\n", (int)dent->d_ino);
        }

        closedir(dp);

        return 0;
}
