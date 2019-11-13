#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

/***************************************************/
void handler(int signo)
{
        psignal(signo, "Received Signal");
        sleep(5);
        printf("In signal Handler, After Sleep\n");
}
/***************************************************/

int main(void)
{
        struct sigaction act;

        sigemptyset (&act.sa_mask);
        sigaddset(&act.sa_mask, SIGQUIT);

        act.sa_flags = SA_RESETHAND;
        act.sa_handler = handler;

        if (sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction");
                exit(1);
        }

        fprintf(stderr, "Input SIGINT : ");
        pause();
        fprintf(stderr, "After Siganl Handler\n");

        return 0;
}