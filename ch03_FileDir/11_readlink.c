#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
        if (argc !=2)
        {
                fprintf(stderr,"Usage : %s sym_lnk_file\n", argv[0]);
                exit(1);
        }
        char *sym_lnk_file = argv[1];

        char buf[BUFSIZ];
        int rd_cnt;
        if((rd_cnt = readlink(sym_lnk_file, buf, BUFSIZ)) < 0)
        {
                perror("readlink");
                exit(1);
        }
        buf[rd_cnt] = '\0';

        fprintf(stdout, "%s : READKLINK = %s\n", sym_lnk_file, buf);

        return 0;
}
