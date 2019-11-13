#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
        if(argc !=2)
        {
                fprintf(stderr, "Usage : %s dir_name\n", argv[0]);
                exit(1);
        }
        char *dir_name = argv[1];
        char *cwd = getcwd(NULL, BUFSIZ);
        if(!cwd)
        {
                perror("getcwd");
                exit(2);
        }
        printf("1.Current Directiory : %s\n", cwd);
        free(cwd);

        if(chdir(dir_name))
        {
                perror("chdir");
                exit(3);
        }

        char wd[BUFSIZ];
        if(getcwd(wd, BUFSIZ))
        {
                printf("2.Current Directory : %s\n", wd);
        }
        else
        {
                perror("getcwd");
                exit(2);
        }

        return 0;
}
