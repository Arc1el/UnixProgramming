#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
        int pd, n;
        char inmsg[BUFSIZ];

        if ((pd = open("./test_fifo", O_RDONLY)) == -1)
        {
                perror("open");
                exit(1);
        }

        printf("Client =====\n");
        write(1, "From Server : ", 13);

        while ((n = read(pd, inmsg, BUFSIZ)) > 0)
                write(1, inmsg, n);

        if (n == -1)
        {
                perror("read");
                exit(1);
        }

        write(1, "\n", 1);
        close(pd);

        return 0;
}
