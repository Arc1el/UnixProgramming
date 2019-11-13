#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
        sigset_t new;

        sigemptyset(&new);
        sigaddset(&new, SIGINT);
        sigaddset(&new, SIGQUIT);
        sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);

        printf("Blocking Signals : SIGINT, SIGQUIT\n");
        printf("Send SIGQUIT\n");
        kill(getpid(), SIGQUIT);

        printf("UnBlocking Siganls\n");
        sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);

        return 0;
}

