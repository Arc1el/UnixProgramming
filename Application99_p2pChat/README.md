# 1:1 Chat Programm


이 프로그램은 파이프 두 개를 활용하여 1:1채팅을 할 수 있는 프로그램입니다. MSG_SIZE로 최대 메시지 길이를 정해줍니다. msg_header를 선언하고 memset으로 비워줍니다. 그후 snpringf를 사용하여 argv로 받은 사용자명을 msg_header에 저장해줍니다. 헤더의 길이를 저장하기위한 hd_length를 선언하고 strlen함수를사용해 할당해줍니다.


양방향으로 데이터를 주고받아야하기 때문에 파이프가 두 개필요합니다. 그렇기에 mkfifo를 사용하여 0666권한으로 두 개를 만들어주는데 생성하는데 실패하고 errno가 EEXIST인경우에는 이미존재하는 fifo파일임을 출력해줍니다.


그후 입력하고 전송할 fd둘을 선언해야하는데 rfd, sfd로 선언해주었고 open함수를 사용하여 전에 만들어준 fifo파일을 열어줍니다. lily는 fifo1을 보내는용도로, fifo2를 받는용도로 사용할것이기 때문에 각각 쓰기전용, 읽기전용으로 열어줍니다.


그후 fd_set구조체 master_set을 선언해줍니다. FD_ZERO함수를 사용하여 초기화 해준 후 rfd와 0을 master_set에 넣어줍니다. 


그후 채팅에서 키보드, 다른프로그램에서 오는 데이터를 모두받아야하므로 select함수를 사용하여 전에 0과 rfd를 저장한 readset을 매개변수로 사용해줍니다. FD_ISSET함수를 사용하여 read_set에 0이 저장되어있다면 read함수를 사용하여 문자열을 읽어옵니다. 그후 write함수를 사용해서 fifo파일에 데이터를 씁니다.


다음은 FD_ISSET함수를 사용하여 rfd에 read_set에 rfd가 저장되어있다면 read함수를 사용하여 fifo에 저장되어있는 메시지를 읽어옵니다. 이때가 다른 프로그램이 보내온 메시지를 읽어오는부분입니다. 그후 wrtie함수를 사용하여 1(stdout)에 문자열을 출력합니다.


지금까지의 설명은 lily를 기준으로 설명한것이며 cara도 fifo일부분만 변경점이 있고 다른부분은 같습니다. 
cara와 lily모두 파이프에서 먼저 데이터를 받으려고하면 둘다 기다리는 현상이 발생할 것입니다. 때문에 cara는 fifo2를 쓰기전용으로 열어줍니다. 이때 lily와 차이점은 열어준 fifo의 순서가 다르다는것입니다. (읽기/쓰기)
select함수에 들어가는 파일기술자도 sfd에서 rfd로 바꾸어줍니다. nfds항목인데 관리하는 파일의 개수입니다. 최대파일 지정번호 +1로 지정하기 때문에 +1이 붙습니다.
