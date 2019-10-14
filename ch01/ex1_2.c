#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
        FILE *fp;

        if((fp = fopen("unix.txt", "r")) == NULL)
                        {
                        printf("errno=%d\n",errno);
                        exit(1);
                        }
        fclose(fp);

        return 0;
}
