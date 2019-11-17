#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

#define TIME_FOR_COOK 3

void sigusr1_handler(int signo);


/*************************************************************************/
void alrm_handler(int signo)
{       //�丮�� �ϼ����� ���
        printf("�ϼ��� �丮�� �����մϴ�.\n");

        kill(getppid(), SIGUSR1); //�θ𿡰� SIGUSR1�ñ׳��� ����
}
/*************************************************************************/
void sigusr1_handler(int signo)
{
        printf("---------- child process ----------\n");
        printf("�ֹ��� �����Ǿ����ϴ�.\n");

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = alrm_handler;

        //ALRM�ñ׳� ������� �˶��ڵ鷯 ȣ��
        if(sigaction(SIGALRM, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction ���� �߻�");
                exit(1);
        }
        //���� �����ð� �� SIGALRM�ñ׳��� ����(�˶��ڵ鷯 ȣ��)
        alarm(TIME_FOR_COOK);
}
/*************************************************************************/

int main(void)
{

        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = sigusr1_handler;

        //SIGALRM, SIGUSR1�� ������ ���ñ׳� ���
        sigset_t block;
        sigfillset(&block);
        sigdelset(&block, SIGALRM);
        sigdelset(&block, SIGUSR1);
        sigprocmask(SIG_SETMASK, &block, NULL);

        //�θ�κ��� SIGUSR1�� �޾ƿ��� ��������(�ڵ鷯 ȣ��)
        if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction ���� �߻�");
                exit(1);
        }

        while(1)
        {
                sleep(999);     //�ñ׳� �߻����� ���
        }

        return 0;
}
