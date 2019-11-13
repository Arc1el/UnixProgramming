#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if(argc !=3)
        {
                fprintf(stderr, "Usage: %s org_file sym_lnk_file\n", argv[0]);
                exit(1);
        }

        char *org_file = argv[1];
        char *sym_lnk_file = argv[2];

        if (symlink(org_file, sym_lnk_file) !=0)
        {
                perror("symlink");
                exit(2);
        }

        return 0;
}
