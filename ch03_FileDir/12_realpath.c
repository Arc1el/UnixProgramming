#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(int argc, char *argv[])
{
        if (argc !=2)
        {
                fprintf(stderr,"Usage : %s filename\n", argv[0]);
                exit(1);
        }
        char *filename = argv[1];
        char resolved_path[PATH_MAX];

        if(!realpath(filename, resolved_path))
        {
                perror("realpath");
                exit(1);
        }

        fprintf(stdout, "%s : REAL_PATH = %s\n", filename, resolved_path);

        return 0;
}
