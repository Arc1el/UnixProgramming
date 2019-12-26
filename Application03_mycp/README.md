# mycp.c

<h3>요구사항</h3>

저수준 파일 입출력을 이용하여 파일을 복사하는 프로그램을 작성하라. 

이때 파일명은 명령행 인자로 받는다. 

실행 예:   ./mycp abc.c def.c

------------------------------------------------------------------------

다음 오류는 반드시 처리되어야 함.

(1) 파일 이름 2개가 없는 경우 사용법을 화면에 출력하고 종료

예: Usage : ./mycp 퍼일이름1 파일이름2

(2) 복사할 소스 파일이 없는 경우 오류 메시지 출력하고 종료

(3) 대상 파일이 이미 존재하는 경우 오류 메시지 출력하고 종료

<h3>구현</h3>

<프로그램 소개>
이 프로그램은 소스파일(원본)을 불러와 복사하여 새로운 파일을 만들도록 하는 프로그램입니다. 유닉스 명령어의 cp명령과 동일합니다.

먼저 소스파일과 대상파일을 불러오기위해 argc와 argv를 메인에서 받았습니다.

./mycp 파일1 파일2 이와 같은 형태로 사용될 것이기 때문에 argv[1]은 원본파일, argv[2]는 대상파일을 의미하 게 됩니다.

먼저 파일2개를 사용자가 명령행 인자로 받지 않을 것을 대비하여 정확히 사용하였을시 argc가 명령행 인자의 개수이므로 3이 될것임을 고려해

argc가 3보다 작을때라는 옵션을 사용하여 반드시 파일두개와 함께사용하 라는 문구와 사용법을 출력해주었습니다.

open함수에 사용될 파일기술자 fd1,2와 read,write함수에 이용될 기술자rd_cnt 3개를 선언해주었습니다.

먼저 open함수로 argv[1]에 해당하는 원본파일을 읽기전용으로 불러와주었습니다. 이때의 파일기술자는 cp1이며 오류가 발생하면 -1값을 리턴하고 에러메세지를 발생시킵니다.

여기서 교수님께서 복사할 소스파일이 존재하지 않 는경우에 존재하지 않음을 따로 출력하라고 하셨는데 어떻게 할까 고민을 하다가 전에 헤더파일을 공부하다가 배운

에러발생시 해당 에러코드값을 errno에 저장하는 errno.h 헤더를 include하면 편하겠다 싶어서 errno ENOENT상수를 사용해주었습니다.

다음은 open함수로 argv[2]에 해당하는 대상파일을 읽기쓰기 전용으로 O_CREAT, O_EXCL플래그를 사용하여 열 어주었습니다.

복사할 대상이 존재하면 에러메세지를 발생시켜야 하기 때문에 O_EXCL플래그까지 사용하여 대상파 일이 존재하는 경우 파일을 생성하지 않고 오류메세지를 출력시켰습니다.

이때도 마찬가지로 에러 발생시 -1을 리 턴하고 에러메세지를 발생시켰고, EEXIST상수를 사용해주었습니다.

이제 원본파일과 대상파일을 둘다 open하여 fd1,2가 가르키므로 fd1의 데이터를 읽어와 fd2에 쓰기를 했어야하는데

read함수로 fd1을 100바이트(BUF_SIZE)씩 불러와 buf배열에 문자열을 저장시켰고 이를 rd_cnt파일 기술자에 할당시켰습니다.

후에 write함수를 호출하여 이 rd_cnt파일기술자에 저장된 문자열들을 fd2에 100바이트 씩 쓰기 해주었습니다.

이때 write함수가 리턴하는값은 자신이 쓰기 한 값이므로 위에서 불러온값과 쓰기한값이 다 르면 -1을 리턴하여 오류메세지를 출력해주었습니다.

그렇게 while 반복문을 진행하다가 rd_cnt값이 0이되는순간 (read의 리턴값 또한 자신이 읽어온 바이트수이기 때문에 읽을것이 없으면 0이됩니다)

반복문은 종료되고 쓰기를 그만두게 됩니다. read함수도 -1을 리턴하게되면 오류발생을 메시지로 출력해주었습니다.