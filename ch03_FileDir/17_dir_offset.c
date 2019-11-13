#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
        if (argc !=2)
        {
                fprintf(stderr,"Usage : %s dir_name\n", argv[0]);
                exit(1);
        }
        char *dir_name=argv[1];

        DIR *dp;
        if((dp=opendir(dir_name))==NULL)
        {
                perror("opendir");
                exit(2);
        }
        printf("** Directory content **\n");
        printf("Start Offset : %ld\n",telldir(dp));

        struct dirent *dent;
        while ((dent=readdir(dp)))
        {
                printf("Read : %20s  ", dent->d_name);
                printf("Cur Offset : %ld\n", telldir(dp));
        }
        printf("** Directory Pointer Rewind **\n");
        rewinddir(dp);
        printf("Cur Offset : %ld\n",telldir(dp));
        printf("** Move Directory Pointer  **\n");
        seekdir(dp,24);
        printf("Cur Offset : %ld\n",telldir(dp));
        dent = readdir(dp);
        printf("Read %20s  ",dent->d_name);
        printf("Next Offset : %ld\n",telldir(dp));
        closedir(dp);
        return 0;
}