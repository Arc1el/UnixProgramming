#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

int pid_child; //�ڽ��� pid�� �Ҵ��ϱ� ���� �������� pid_child����
sigset_t block; //����� �ñ׳�����

/********************************************************************/
void int_handler(int signo)
{
        //�ֹ��� ���»��¿��� SIGINT �Ǵ� SIGQUIT�ñ׳��� ���°��
        kill(pid_child, SIGINT); //�ڽ�����
        printf("\n�ڽ� ���μ����� �����Ͽ����ϴ�.\n");
        exit(0); //�ڽ�����
}
/********************************************************************/
void sigusr1_handler(int signo)
{
        struct sigaction act;
        act.sa_flags = 0;
        //�ڽ����κ��� SIGUSR1 �ñ׳��� ���� �丮 ����
        printf("---------- parent process ----------\n");
        printf("�ϼ��� �丮�� ���޹޾� �մԿ��� �����Ͽ����ϴ�.\n");

        sigemptyset(&block); //����Ͽ��� �ñ׳����� �����
        sigprocmask(SIG_SETMASK, &block, NULL);

        act.sa_handler = int_handler; //SIGINT�� ���°�� �ٽ� int_handler�� ����
        if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
        {
                perror("sigaction ���� �߻�");
                exit(3);
        }
}
/********************************************************************/

int main(void)
{

        pid_child = fork();

        if(pid_child < 0)
        {
                perror("fork �����߻�");
                exit(1);
        }
        //�ڽ����μ����ΰ�� exec�� ���α׷��� ��ü�� c_cook.exe�� ���� 
        else if(pid_child == 0)
        {
                if(execl("./c_cook.exe", "c_cook.exe", NULL) < 0)
                {
                        perror("execl ���� �߻�");
                        exit(2);
                }
        }
        //�θ����μ����ΰ��
        else
        {

                struct sigaction act;
                sigemptyset(&act.sa_mask);
                act.sa_flags = 0;
                act.sa_handler = int_handler;
                //�ֹ��� SIGINT�ñ׳� �߻��ϴ°��
                if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
                {
                        perror("sigaciton ���� �߻�");
                        exit(3);
                }

                while(1)        //�ݺ��ؼ� �޴����
                {
                        sigemptyset(&block);
                        sigprocmask(SIG_SETMASK, &block, NULL);
                        printf("---------- parent process ----------\n");
                        printf("������ �ֹ��Ͻðڽ��ϱ�? (y/n) : ");
                        char answer;
                        scanf("%c", &answer);

                        switch(answer)
                        {
                                case 'Y' :
                                case 'y' : //�ֹ��� ������ SIGUSR1�� ������ ���ñ׳� ���
                                        sigfillset(&block);
                                        sigdelset(&block, SIGUSR1);
                                        sigprocmask(SIG_SETMASK, &block, NULL);
                                        act.sa_handler = sigusr1_handler;
                                        //����ڷκ��� �ֹ��޾� �ڽ����μ������� �ֹ�����
                                        if(sigaction(SIGUSR1, &act, (struct sigaction *)NULL) < 0)
                                        {
                                                perror("sigaction ���� �߻�");
                                                exit(3);
                                        }
                                        kill(pid_child, SIGUSR1); //�ڽĿ��� SIGUSR1 �ñ׳� ����
                                        printf("�ֹ��� ��û�Ͽ����ϴ�.\n");
                                        pause();
                                        break;
                                case 'N':
                                case 'n':
                                        printf("�ֹ����α׷��� �����մϴ�.\n");
                                        exit(0);
                                default :
                                        printf("�߸��� �Է��Դϴ�. y or n\n");
                                        exit(4);
                        }
                        getchar();
                }
        }
}
