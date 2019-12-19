# 기말시험

사용한 헤더
```c
#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>
```

사용한 사용자 정의함수 
```c
void log_now(int select, char menu[]);
```

사용한 함수
```c
kill(pid_child, SIGINT);
printf("\n\n[부모] 자식 프로세스를 종료하였습니다.\n");
exit(0);
pipe(c2k_fd);
perror("pipe");
fork();
close(c2k_fd[1]);
dup2(c2k_fd[0], 0);
execl("./kitchen.exe", "kitchen.exe", NULL);
sigemptyset(&act.sa_mask);
sigaction(SIGINT, &act, (struct sigaction *)NULL);
fgets(menu, MENU_SIZE, stdin);
write(c2k_fd[1], menu, strlen(menu);
read(k2c_fd[0], buf, BUFSIZ);
strncmp("success", buf, 7);
open("log.txt", O_WRONLY | O_CREAT | O_APPEND , 0644 );
sprintf(logbuf, "%d년 %d월 %d일 %d시 %d분 %d초 주문전달 메뉴 : %s");
fprintf(stderr, "[자식] 완성된 요리를 전달합니다.\n\n");
alarm(TIME_FOR_COOK)
```
시스템콜
```c
kill();
//0 성공 -1실패
//kill() 함수는 쉘에서 프로세스를 죽이는 kill 명령과는 달리 프로세스에 시그널을 전송합니다. 물론 프로세스에 SIGKILL을 보내면 쉘 명령의 kill 과 같은 역활을 합니다.

exit();
//int	main() 함수의 반환값에 해당하는 정수
//exit()는 프로그램을 종료합니다.

pipe();
//0 성공 -1실패
//프로세스 끼리의 통신(IPC)에서 사용하는 파이프를 생성합니다. pipe()에서 생성하는 파이프는 프로세스 안에 생성되는 것이 아니라 커널에 생성되며 프로세스에는 다만 파이프를 이용할 수 있는 파일 디스크립터만 제공됩니다. 그러므로 하나의 프로세스에서 파이프를 생성했다고 해도 다른 프로세스에서 그 디스크립터를 사용할 수 있다면, 그 디스크립터를 이용하여 서로 통신할 수 있습니다.

perror();
//에러 내용을 출력합니다

fork();
//fork()는 현재 실행되는 프로세스에 대해 복사본 프로세스를 생성합니다.
//실행에 실패하면 -1 을 반환. 부모에게는 새로 생성된 자식 프로세스 PID가 반환되며, 자식 프로세스에는 0이 반환됩니다.

close();
//정상적으로 close 했다면 0을, 실패했다면 -1을 반환
//open() 함수로 열기를 한 파일 사용을 중지합니다. open()함수는 fcntl.h 에 정의 되어 있지만 write(), read(), close()는 unistd.h에 정의 되어 있습니다.

dup2();
//원하는 파일 디스크립터 번호, 실패하면 -1 이 반환됩니다.
//파일 디스크립터 복사본을 만듭니다. dup()는 커널에서 알아서 사용하지 않는 디스크립터 번호 중에 하나가 자동으로 지정되지만 dup2()는 프로그래머가 원하는 번호로 지정할 수 있습니다. 프로그래머가 지정하는 번호가 이미 사용하는 번호라면 dup2()는 자동으로 그 파일을 닫고 다시 지정해 줍니다.

sigaction();
//0 성공 -1실패
//sigaction() 함수는 signal() 보다 향상된 기능을 제공하는 시그널 처리를 결정하는 함수입니다. signal()에서는 처리할 행동 정보로 시그널이 발생하면 호출이될 함수 포인터를 넘겨 주었습니다. 그러나 sigaction()에서는 struct sigaction 구조체 값을 사용하기 때문에 좀더 다양한 지정이 가능합니다.

write();
//open() 함수로 열기를 한 파일에 쓰기를 합니다. open()함수는 fcntl.h 에 정의 되어 있지만 write(), read(), close()는 unistd.h에 정의 되어 있습니다.
//정상적 쓰기를 했다면 쓰기를 한 바이트 개수를, 실패했다면 -1을 반환

read();
//open() 함수로 열기를 한 파일의 내용을 읽기를 합니다.
//정상적으로 실행되었다면 읽어들인 바이트 수를, 실패했다면 -1을 반환

open();
//파일을 open할 때에는 용도에 따라 읽기 전용, 쓰기 전용 또는 읽기와 쓰기가 모두 되는 옵션을 지정하여 열기를 합니다.
//정상으로 open했다면 파일 디스크립터의 양의 정수 값. 실패하면 -1을 반환

alarm();
//지정한 시간이 되면 자기 자신에게 SIGALRM 시그널을 전송합니다. 프로세스는 SIGALRM을 받으면 종료되므로 이를 유의하셔야 합니다.
//	양수	이전에 alarm() 호출로 시그널이 발생하기 까지 남은 시간, 0	이전에 설정된 알람이 없다
```

라이브러리
```c
printf();
fprintf();
exec();
fgets();
strncmp();
sprintf();
```

사용한 상수
```c
#define MENU_SIZE 128;
//char menu[MENU_SIZE]사용할때 사용 이때의 메뉴는 사용자에게 입력받은 메뉴(주문)





