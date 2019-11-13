#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if (argc!=2)
        {
                fprintf(stderr,"usage : %s filename\n", argv[0]);
                exit(1);
        }

        int fd = open(argv[1], O_RDONLY);
        if(fd<0)
        {
                perror("open");
                exit(1);
        }

        struct stat buf;

        if(fstat(fd,&buf)==0)
        {
                printf("Inode = %d\n", (int)buf.st_ino);
                printf("Mode = %o\n", (unsigned int)buf.st_mode);
                printf("GID = %d\n", (int)buf.st_gid);
                printf("SIZE = %d\n", (int)buf.st_size);
                printf("Atime = %d\n", (int)buf.st_atime);
                printf("Mtime = %d\n", (int)buf.st_mtime);
                printf("Ctime = %d\n", (int)buf.st_ctime);
                printf("Blksize = %d\n", (int)buf.st_blksize);
                printf("Blocks = %d\n", (int)buf.st_blocks);
        }
        else
        {
                perror("fstat");
        }
        close(fd);

        return 0;
}
