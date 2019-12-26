#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<sys/sysinfo.h>
#include<sys/types.h>
#include<unistd.h>

void print_uts();
void print_sysinfo();
void print_sysconf();
void getdelim_file();

int main(int argc, char *argv[])
{
        int opt;
        struct utsname uts;
        if(argc<2)
        {
                fprintf(stderr, "이 프로그램은 파일명과 옵션을 사용해야합니다.\n"
                                "사용법 : %s -(옵션)\n"
                                "-a 모든정보 출력(cpu세부정보 제외) \n-m 머신타입 출력\n-n 노드이름 출력\n"
                                "-o 운영체제 정보 출력 \n-r 운영체제 릴리즈 버전 출력 \n"
                                "-s 운영체제 이름 출력 \n-v 운영체제 정보출력 \n-c cpu정보 출력\n",
                                argv[0]);
                exit(1);
        }
        if(uname(&uts) == -1)
        {
                perror("uname");
                exit(2);
        }

        while((opt = getopt(argc, argv, "auifmnorsvc")) != -1)
        {
                 switch(opt)
                 {
                        case 'a': //print all
                                print_uts();
                                print_sysinfo();
                                print_sysconf();
                                printf("\n====== 운영체제 정보 ======\n");
                                getdelim_file("/etc/os-release", "0");
                                printf("====== 운영체제 릴리즈 버전 ======\n");
                                printf("Release : %s\n", uts.release);
                                getdelim_file("/etc/redhat-release", "0");
                                printf("====== 운영체제  정보 ======\n");
                                getdelim_file("/proc/version", "1");
                                break;
                        case 'u'://uname구조체 
                                print_uts();
                                break;
                        case 'i'://시스템 통계정보
                                print_sysinfo();
                                break;
                        case 'f'://시스템자원정보
                                print_sysconf();
                                break;
                        case 'm': //시스템 하드웨어타입 (machine)
                                printf("====== 머신(하드웨어)타입 ======\n");
                                printf("Machine : %s\n", uts.machine);
                                break;
                        case 'n': //노드이름 (nodename)
                                printf("====== 노드이름  ======\n");
                                printf("Node name : %s\n", uts.nodename);
                                break;
                        case 'o': //운영체제정보 (OS)
                                printf("====== 운영체제 정보 ======\n");
                                getdelim_file("/etc/os-release", "0");
                                break;
                        case 'r': //커널배포버전(kernel release)
                                printf("====== 운영체제 릴리즈 버전 ======\n");
                                printf("Release : %s\n", uts.release);
                                getdelim_file("/etc/redhat-release", "1");
                                 break;
                        case 's': //운영체제 이름 (sys name)
                                printf("====== 운영체제 이름  ======\n");
                                printf("OS name : %s\n", uts.sysname);
                                break;
                        case 'v': //운영체제 버전정보 (kernel version)
                                printf("====== 운영체제  정보 ======\n");
                                getdelim_file("/proc/version", "1");
                                break;
                        case 'c': //cpu 정보 (cpu)
                                printf("====== cpu 정보 ======\n");
                                getdelim_file("/proc/cpuinfo", "1");
                                break;
                }
        }
        return 0;
}

void print_uts(void)
{
        struct utsname uts;

        if(uname(&uts) == -1)
        {
                perror("uname");
                exit(2);
        }
        }

        printf("OSname : %s\n", uts.sysname);
        printf("Nodename : %s\n", uts.nodename);
        printf("Release : %s\n", uts.release);
        printf("Version : %s\n", uts.version);
        printf("Machine : %s\n", uts.machine);
}

void print_sysinfo(void)
{
        struct sysinfo sys;

        sysinfo(&sys);
        printf("부팅 이후 지나간 초단위 시간 : %ld\n", sys.uptime);
        printf("1, 5, 15 분 부하 평균 : %lu\n", sys.loads);
        printf("사용할 수 있는 총 메모리 크기 : %lu\n", sys.totalram);
        printf("이용할 수 있는 메모리 크기 : %lu\n", sys.freeram);
        printf("공유 메모리의 양 : %lu\n", sys.sharedram);
        printf("버퍼에 의해 사용된 메모리 : %lu\n", sys.bufferram);
        printf("총 스왑 공간의 크기 : %lu\n", sys.totalswap);
        printf("이용할 수 있는 스왑 공간 : %lu\n", sys.freeswap);
        printf("현재 프로세스의 수 : %hd\n", sys.procs);
}

void print_sysconf(void)
{
        printf("argv[]와 envp[]를 합한 최대길이 : %ld \n", sysconf(_SC_ARG_MAX));
        printf("한 UID에 허용되는 최대 프로세스 개수 : %ld \n", sysconf(_SC_CHILD_MAX));
        printf("초당 클록 틱 수 : %ld \n", sysconf(_SC_CLK_TCK));
        printf("프로세스당 열 수 있는 최대파일 개수 : %ld \n", sysconf(_SC_OPEN_MAX));
        printf("패스워드의 최대길이 : %ld \n", sysconf(_SC_PASS_MAX));
        printf("로그인명의 최대길이 : %ld \n", sysconf(_SC_LOGIN_NAME_MAX));
        printf("시스템 메모리의 페이지 크기 : %ld \n", sysconf(_SC_PAGESIZE));
}

void getdelim_file(char *path, int opt)
{
        FILE *fp;
        while((fp=fopen(path,"r")) == NULL)
        {
                perror("fopen");
                exit(3);
        }

        int delim;
        switch(opt)
        {
                case '0' : //getline
                delim = '\n';
                        break;
                case '1' :
                        delim = 0;
                        break;
        }

        size_t size = 0;
        char *lineptr = NULL;
        while(getdelim(&lineptr, &size, delim, fp) != -1)
        { //lineptr가 널, size가 0으로 설정되어있으면 getdelim에서 버퍼를 할당
                puts(lineptr);
        }
        free(lineptr); //할당된 메모리 해제
        fclose(fp);
}
