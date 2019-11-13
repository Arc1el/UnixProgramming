#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                fprintf(stderr, "Usage : %s filename\n", argv[0]);
                exit(1);
        }

        char *filename = argv[1];
        struct stat buf;

        stat(filename, &buf);
        printf("Mode =  %o (16Áø¼ö : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

        int kind;
        kind = buf.st_mode & S_IFMT;
        printf("Kind = %x\n", kind);

        switch (kind)
        {
                case S_IFIFO:
                        printf("%s : FIFO\n", filename);
                        break;
                case S_IFDIR:
                        printf("%s : Directory\n", filename);
                        break;
                case S_IFREG:
                        printf("%s : Regular File\n", filename);
                        break;
        }
        return 0;
}
