#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if (argc!=2)
        {
                fprintf(stderr, "Usage : %s filename\n", argv[0]);
                exit(1);
        }

        char *filename = argv[1];
        struct stat buf;

        stat(filename, &buf);
        printf("Mode = %o (16Áø¼ö : %x)\n", (unsigned int)buf.st_mode,(unsigned int)buf.st_mode);

        if(S_ISFIFO(buf.st_mode)) printf("%s FIFO: \n", filename);
        if(S_ISDIR(buf.st_mode)) printf("%s : Directory\n", filename);
        if(S_ISREG(buf.st_mode)) printf("%s : Regular File\n", filename);

        return 0;
}