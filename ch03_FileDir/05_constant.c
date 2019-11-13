#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[])
{
        if(argc!=2)
        {
                fprintf(stderr, "Usage : %s filename\n",argv[0]);
                exit(1);
        }

        char *filename = argv[1];
        struct stat buf;

        stat(filename, &buf);
        printf("Mode = %o (16Áø¼ö : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

        if((buf.st_mode & S_IREAD) !=0)
                        printf("%s : user has a read permission\n",filename);

        if((buf.st_mode & (S_IREAD >> 3)) !=0)
                        printf("%s : group has a read permission\n",filename);

        if((buf.st_mode & S_IROTH) !=0)
                        printf("%s : other has a read permission\n",filename);

        return 0;
}
