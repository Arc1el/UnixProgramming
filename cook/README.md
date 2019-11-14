# cook
부모 프로세스 기능

1. 부모 프로세스는 반복해서 메뉴를 출력
- while문을 사용하여 반복해서 메뉴출력해주었습니다.

2. 사용자로부터 주문을 받아 자식 프로세스에게 주문 내용 전달.(SIGUSR1)
- scanf로 문자를 받아 y혹은 Y일 경우 자식프로세스에게 SIGUSR1시그널을 보내주었습니다. (kill함수 사용)

3. 일단 주문을 받으면 SIGUSR1을 제외한 다른 시그널은 모두 무시
- sigaction 구조체를 사용하여 주문이 들어온 후 sa_mask의 비트를 fillset으로 전부 1로 처리 한 후 다시 delset으로 SIGUSR1시그널만 제외해주었습니다. 이렇게할 경우 SIGUSR1시그널을 제외한 시그널들이 블록처리됩니다.

4. 자식으로부터 SIGUSR1(요리 완료)가 오면 화면에 출력 (요리 제공)
- pause함수로 SIGUSR1시그널이 올때까지 대기하다가 오는 경우 sigaction으로 sigusr1_handler가 처리하도록 해주었습니다. 화면 출력은 핸들러에서 동작합니다.

5. 주문이 없는 상태에서 SIGINT 또는 SIGQUIT 시그널이 들어오는 경우 자식을 먼저 종료시킨 후 자신도 종료
- int_handler를 작성하여 주문을 받기전 sa_handler로 int_handler를 지정해주고 SIGINT시그널이 들어오는 경우 int_handler가 처리하도록 하였습니다. int_handler는 자식에게 kill함수를 사용하여 인터럽트 시그널을 보내고 wait함수를 사용하여 대기합니다. 그후 자식프로세스를 종료하였다는 문구를 출력후 exit함수로 자신(부모)를 종료합니다.
 

자식 프로세스

1. 부모로부터 주문(SIGUSR1)을 받으면 조리를 시작
- main함수에서 sigusr1함수가 들어오면 sigaction함수를 통해 sigusr1핸들러가 처리하도록 동작합니다. sigusr1핸들러는 주문접수 문구를 출력하고 SIGALRM을 제외한 모든 시그널을 블록합니다. sa_handler를 alrm_handler로 지정한 후 sigaction함수를 사용하여 ALRM시그널이 

2. 일단 조리를 시작하면 음식이 완성되기 전까지 SIGALARM을 제외한 다른 시그널은 모두 무시
- 조리시작시 sigusr1핸들러가 처리하게됩니다. 그후 핸들러 안에서 fillset으로 sa_mask를 모두 1로 만들어주고 sigdelset으로 SIGALRM을 제외해주었습니다. 이렇게되면 SIGALRM을 제외한 다른 시그널들은 블록처리하게됩니다.

3. 일정 조리시간이 지내면(alarm 이용) 음식이 완성되고, 이를 부모 프로세스에게 알린다(SIGUSR1)
- sigaction으로 alrm시그널이 올 경우 alrm핸들러에서 처리하게되고 완성된 요리를 전달한다라는 문구를 출력합니다. 그후 kill함수를 사용하여 부모프로세스에 SIGUSR1시그널을 보냅니다. (kill(getppid(),SIGUSR1))

4. 음식이 완성되면 다른 시그널을 받을 수 있도록 전환
- 음식이 완성된 다음 다른 시그널을 받을 수 있도록 sa_mask를 emptyset을 사용하여 비트를 0으로 설정해주었습니다.
