#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
        if(access("unix.txt",F_OK) == -1)
                        {
                        printf("errno=%d\n",errno);
                        }

        return 0;
}
