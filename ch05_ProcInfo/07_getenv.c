#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                fprintf(stderr,"Usage : %s env_name\n", argv[0]);
                exit(1);
        }

        char *env_name=argv[1];
        char *val;
        val=getenv(env_name);
        if(val==NULL)
                printf("%s not defined\n", env_name);
        else
                printf("%s = %s\n", env_name, val);

        return 0;
}