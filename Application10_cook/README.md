# cook

![Image of Result](https://github.com/Arc1el/UnixProgramming/blob/master/Application10_cook/result.png)

주문-조리 프로그램
1. 부모 프로세스 - 손님 접대 (주문 및 요리 제공)
2. 자식 프로세스 - 조리 (요리 시작 - 완료)


부모 프로세스 기능


1.부모 프로세스는 반복해서 메뉴를 출력
- while문을 사용하여 반복으로 출력해주었습니다.

2. 사용자로부터 주문을 받아 자식 프로세스에게 주문 내용 전달.(SIGUSR1)
- scanf를 사용하여 answer가 y 또는 Y인 경우 자식에게 SIGUSR1시그널을 보내 주문을 전달하였습니다.

3. 일단 주문을 받으면 SIGUSR1을 제외한 다른 시그널은 모두 무시
- sigaction함수를 사용하여 for루프문을 돌려 SIGUSR1을 제외한 시그널의 핸들러를 SIG_IGN으로 지정해줌으로써 다른시그널들을 무시하도록 동작하였습니다.

4. 자식으로부터 SIGUSR1(요리 완료)가 오면 화면에 출력 (요리 제공)
- pause함수로 SIGUSR1시그널이 올때까지 대기하다가 오는 경우 sigaction으로 sigusr1_handler가 처리하도록 해주었습니다. 화면 출력은 핸들러에서 동작합니다.

5. 주문이 없는 상태에서 SIGINT 또는 SIGQUIT 시그널이 들어오는 경우 자식을 먼저 종료시킨 후 자신도 종료
- int_handler를 작성하여 주문을 받기전 sa_handler로 int_handler를 지정해주고 SIGINT시그널이 들어오는 경우 int_handler가 처리하도록 하였습니다. int_handler는 자식에게 kill함수를 사용하여 인터럽트 시그널을 보내고 wait함수를 사용하여 대기합니다. 그후 자식프로세스를 종료하였다는 문구를 출력후 exit함수로 자신(부모)를 종료합니다.

자식 프로세스
1. 부모로부터 주문(SIGUSR1)을 받으면 조리를 시작
- main함수에서 sigusr1함수가 들어오면 sigaction함수를 통해 sigusr1핸들러가 처리하도록 동작합니다.(조리시작)

2. 일단 조리를 시작하면 음식이 완성되기 전까지 SIGALARM을 제외한 다른 시그널은 모두 무시
- sigaction 함수를 사용하여 sa_handler를 SIG_IGN으로 설정 후 for루프문을 사용하여 SIGALRM시그널을 제외한 다른시그널들을 무시하도록 설정해주었습니다.

3. 일정 조리시간이 지내면(alarm 이용) 음식이 완성되고, 이를 부모 프로세스에게 알린다(SIGUSR1)
sigaction으로 alrm시그널이 올 경우 alrm핸들러에서 처리하게되고 완성된 요리를 전달한다라는 문구를 출력합니다. 그후 kill함수를 사용하여 부모프로세스에 SIGUSR1시그널을 보냅니다. (kill(getppid(),SIGUSR1))

4. 음식이 완성되면 다른 시그널을 받을 수 있도록 전환
- sigaction 함수를 사용하여 sa_handler를 SIG_DFL로 설정후 for루프문을 사용하여 시그널들을 디폴트 동작으로 수행되도록 바꾸어주었습니다.
