# mycat.c

<h3>요구사항</h3>

저수준 파일 입출력을 이용하여 mycat 프로그램을 작성하라. 

이때 출력시 행 번호를 붙여서 출력하고, 파일 명은 명령행 인자로 받는다. 

실행 예:  ./mycat han.c

<h3>구현</h3>

이 프로그램은 저수준 파일 입출력을 통해서 파일 하나를 명령행 인자로 받아 이 파일을 다시 행 번호를 붙여서 출력 하게 하는 프로그램입니다.

프로그램을 설계할 때, 행이 나눠지는 시점은 \n 개행문자가 있으므로 이 점을 활용하여 개행문자 다음에 행 번호가 출력되도록 코드를 작성하였습니다.

파일명을 명령행 인자를 통해 받으므로 argc와 argv 를 main함수에서 정의하였습니다.

그리고 파일을 한번 open할 때, 파일을 read할 때 필요한 파일기술자 2개를 opn 과 rd로 선언해주었고 i는 후에 사용될 반복문 때문에,

line은 행번호를 할당하기위해 1로 초기화하여 선언해주었습니다. 그후 open함수를 통해 argv[1]을 읽기전용으로 불러왔습니다.

argv[0]이 ./mycat 이고, argv[1]이 파일명이 될 것이기 때문입니다. 이때 오류가 발생하여 -1이 리턴되면 에러메세지 발생후 종료되도록 하였습니다.

그후 예제에서 한 것과 같이 while문을 이용해 opn파일기술자(opn(argv[1]))의 해당파일의 100바이트를 buf에 저장하게 하였습니다.

rd는 read함수가 불러온 바이트수를 리턴하기 때문에 후에 불러올 내용이 없다면 while문을 종료합니다.

그렇게 %c문자열과 반복문을 통하여 buf에 저장된 바이트를 하나씩 print문으로 찍어내게 하였고 if문을이용해 \n개행문자 를 만나게 되는 경우 행번호를 찍어주도록 하였습니다.

더 이상 불러올것이 없어 while문이 종료되면 read함수가 -1 을 리턴한 경우 에러메세지 후 종료하도록 하였고 파일을 모두 불러왔다는 메시지를 출력해주었습니다.

프로그램을 작성 한 후 1행이 제대로 표시되지 않는 것을 볼 수 있었는데 파일을 읽어와 print문으로 찍어내기전,

즉 파일을 read하기전에는 첫1행은 수동으로 표시해줘야하기 때문에 printf("%2d : ", line++);로 임의로 1행을 출력해주 었습니다.

또한 사용자가 명령행인자를 입력하지 않은 경우, 여러 인자를 입력한 경우를 생각하여 argc값을 통해 1개 이상의 파일명으로 포함하라,

1개의 파일명밖에 사용이 불가능 하다는 메시지를 출력해주었습니다.
