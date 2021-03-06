# hanopt.c

<h3>요구사항</h3>

명령행 인자와 getopt 함수를 이용하여 다음 명령을 처리하는 프로그램을 작성하라.

(1) 명령어 이름은 hanopt

(2) 명령의 옵션과 동작

인자가 없을 경우 : -h와 같이 사용 가능한 옵션 목록 출력

-a "Welcome to UNIX System Programming!" 출력

-u 인자 "Nice to meet 인자" 형태로 출력

-h 사용 가능한 옵션 목록 출력 

<h3>구현</h3>

이 프로그램은 hanopt실행파일에 다양한 옵션의 명령행인자를 사용하여 각기 다른 결과를 출력하는 프로그램입니다.

먼저, 명령행 인자를 받기위해 main에서 argc, *argv[]를 받았습니다.

또한 외부에서 받아온 문자열이 -u옵션에 필 요하기 때문에 extern char *optarg 또한 선언하였습니다.

argc값을 이용하여 2보다 작은 경우, 즉 명령행 인자를 받지 않은 경우 1개이상의 명령행인자와 사용하라는 에러메시지와 함께

-h옵션과 같은 사용법에대한 내용을 출력해주었습니다.

각 case마다 argc값을 이용하여 여러옵션과 사용이 불가능하다는 메시지를 출력해주었습니다.

단 u 옵션의 경우엔 다른옵션과는달리 1개의 인자를 더받아야 하므로 3보다 작을경우를 조건으로 사용하였습니다.

첫 제출물에서는 default의 경우 -h옵션과 똑같이 출력하게 하여 오류 발생시에 명령행인자를 받지 않았다던가 엉뚱 한 인자를 입력하였는가 하는 부분이 모호했기 때문에

명령행인자를 받지 않은 경우 위에 서술된 내용과 같이 argc<2를 이용해 따로 메시지를 빼주었고 이제 엉뚱한명령행인자,

불필요한 인자등을 사용하였을 경우에 잘못된 옵 션을 사용하였으므로 h옵션을 사용하여 사용법을 숙지해 달라는 메시지를 출력하게 하였습니다.
