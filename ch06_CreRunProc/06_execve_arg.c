
#include<stdio.h>
  
int main(int argc, char **argv, char **envp)
{
        int n;
        char **env;

        printf("\n --> In %s Main\n", argv[0]);

        printf("argv = %d\n", argc);
        for(n=0; n<argc; n++)
                printf("argv[%d] = %s\n", n, argv[n]);

        env= envp;
        while(*env)
        {
                printf("%s\n",*env);
                env++;
        }

        return 0;
}
