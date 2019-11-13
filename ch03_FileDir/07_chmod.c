#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
                fprintf(stderr,"Usage : %s filename\n",argv[0]);
                exit(1);
        }

        char *filename = argv[1];
        if (access(filename, F_OK) != 0)
        {
                fprintf(stderr, "%s : not exist !\n", filename);
                exit(2);
        }

        struct stat buf;

        chmod(filename, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
        stat(filename, &buf);
        printf("1.Mode = %o\n", (unsigned int)buf.st_mode);

        buf.st_mode |= S_IWGRP;
        buf.st_mode &= ~(S_IROTH);
        chmod(filename, buf.st_mode);
        stat(filename, &buf);
        printf("2.Mode = %o\n", (unsigned int)buf.st_mode);

        return 0;
}
