# mycpExtended.c

<h3>요구사항</h3>

응용과제 3 확장

--------------------------------------

옵션 x : 복사할 파일이 존재하는 경우 오류 메시지 출력하고 종료하기

옵션 t : 복사할 파일이 존재하는 경우 무조건 지우고 복사하기

옵션 y : 복사할 파일이 존재하는 경우 사용자에게 메시지를 출력하고, 사용자가 y를 답하는 경우 지우고 복사, 그렇지 않는 경우 종료.

옵션이 지정되지 않으면 옵션 x로 동작.

---------------------------------------------

추가 : 사용자가 여러 옵션을 지정한 경우 제일 마지막에 설정한 옵션으로 동작

<h3>구현</h3>

먼저 프로그램의 맨처음에 argc확인을 위해 서 조건문을 넣었습니다. 조건은 다음과같이 생각하여

./m unix.txt unix.bak : argc 3 optind 1,

./m -x uni.txt : argc 3 optind 1,

./m -x -t unix.txt unix.bak : argc 5 optind 1,

./m -x unix.txt unix.bak : argc 4 optind 1,

./m unix.txt : argc2 optind1 (argc-optind)한값이 2보다 작은경우를 조건으로 주었습니다.

옵션으로 인해 argv[1],argv[2]등을 직접 사용할 수 없기 때문에 getopt 루프문 이후에

file1, file2에 argv[argc-optind+1], argv[argc-optind+2]를 이용하여 원본파일과 대상파일을 할당해주었습니다.

open, read, write의 경우 stderr가아닌 perror로 처리해주었습니다.

변수이름을 fd1, fd2, rd_cnt, opt, answer등 의미를 임작할 수 있는 변수명을 활용해주었습니다.

<문제점>

1. 프로그램에 옵션이 없는 경우 (./mycp3 unix.txt unix.bak) x옵션으로 동작하지 못합니다.

처음 default와 case '?'의 경우를 활용하려고 하였는데 몇 번을 시도해도 되지않아서 생각해보니 아예 getopt함수를 호출하지 못하 여 발생하는 문제인 것 같습니다.

그래서 이러한경우엔 getopt 루프문 이전에 argc검사단계에서 x옵션처럼 동작하려 고 file1이 읽기가능하면 실행하려고 작성하였는데

./mycp3 -x unix.txt 이런 명령행 인자를 받으면 -x 또한 읽기가 능하여 실패하였습니다.

2. 마지막에 설정한 옵션으로 동작하는 경우, 처음에는 optind값을 임의로 +하여 사용했는데 optind임의로 변경하는 것이 부적절하다 하여서

argc-optind>1인경우와 argv[optind]가 file1인경우를 생각하였습니다. optind값은 getopt 함수가 한번 호출될때마다 +1 되기 때문에 이 조건을 사용하였는데

./mycp3 -x -t unix.txt unix.bak같은 명령을 주게되면 -x는 스킵되지만 -t로 동작하지 않는등의 문제가 발생했습니다.

이부분에 대해서는 저는 getopt루프문을 돌 려 함수가 호출되면 optind가 1이 늘어나는점을 활용하여 조건을 내건 것인데 이상하게

optind가 +1되지않아 -x가 스킵되고 -t로 동작하려는 순간 optind가 그대로이기 때문에 -t또한 스킵하려는 문제가 발생하였습니다.
