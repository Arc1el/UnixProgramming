#include<sys/errno.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

extern int errno;

int main(int argc, char *argv[])
{
        if(argc !=2)
        {
                fprintf(stderr, "Usage : %s filename\n", argv[0]);
                exit(1);
        }

        char *filename = argv[1];

        int chk_result;
        if (access(filename, F_OK) == -1 & errno == ENOENT)
                printf("%s : File not exist.\n", filename);

        chk_result = access(filename, R_OK);
        if (chk_result == 0)
                printf("%s : Read permission is permitted.\n", filename);
        else if(chk_result == -1 && errno == EACCES)
                printf("%s : Read permission is not permitted.\n", filename);

        return 0;
}
