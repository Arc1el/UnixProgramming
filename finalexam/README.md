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
exit();
pipe();
perror();
fork();
close();
dup();
sigaction();
write();
read();
open();
close();
alarm();
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




