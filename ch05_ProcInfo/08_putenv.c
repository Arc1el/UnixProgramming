#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if(argc!=3)
        {
                fprintf(stderr,"Usage : %s env_name new_value\n", argv[0]);
                exit(1);
        }

        char *env_name=argv[1];
        char *new_value=argv[2];

        char *val;
        val = getenv(env_name);
        if(val==NULL)
                printf("%s not defined\n",env_name);
        else
                printf("1. %s = %s\n",env_name, val);

        char new_env_str[BUFSIZ];
        sprintf(new_env_str, "%s=%s", env_name, new_value);
        putenv(new_env_str);

        val = getenv(env_name);
        if(val==NULL)
                printf("%s not defined\n", env_name);
        else
                printf("2. %s = %s\n", env_name, val);

        return 0;
}
