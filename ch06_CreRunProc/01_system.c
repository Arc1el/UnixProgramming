#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
        if(argc<2)
        {
                fprintf(stderr, "Usage : %s cmd_name [cmd_opt ... ]\n", argv[0]);
                exit(1);
        }

        char cmd_line[BUFSIZ];
        int i;
        int remaining_len=BUFSIZ;
        int argv_str_len;

        for(i=1; (i<argc) && (remaining_len>0); i++)
        {
                argv_str_len = strlen(argv[i]);
                strncat(cmd_line, argv[i], remaining_len);
                remaining_len = BUFSIZ - strlen(cmd_line);
                if(remaining_len>0)
                {
                        strncat(cmd_line, " ",1);
                        remaining_len--;
                }
        }

        if(i!=argc)
        {
                fprintf(stderr, "insufficient cmd_line_buffer\n", argv[0]);
                exit(2);
        }

        printf("Cmannd line : %s\n",cmd_line);

        int cmd_result;

        cmd_result = system(cmd_line);
        printf("Return Value : %d\n", cmd_result);


        return 0;
}