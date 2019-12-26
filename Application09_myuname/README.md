# myuname.c

<h3>요구사항</h3>

uname, sysinfo, sysconf 함수 등을 사용해 my_uname 명령을 만든다.

이때  getopt()를 이용하여 관련 정보를 출력한다.

기본 200점 + (제공하는 정보 수 * 20점)

반드시 제공하는 정보와 관련 옵션 문자 설명 포함시킬 것!

<h3>구현</h3>

getdelim을 사용하기위해 _GNU_SOURCE를 정의해주었습니다. utsname구조체와 sysinfo구조체를 사용하여 정보 를 출력하기위해 헤더를 인클루드 해주었습니다.

그 후 함수를 선언해주었고 utsname구조체 uts를 선언하였습니다.

argc가 2 미만인경우를 조건으로 사용하여 파일명과 옵션을 받도록 하였고, 조건을 만족하지 못할 경우 에러메세 지와 사용법을 출력해주었습니다.

uname함수를 사용하여 uts구조체에 운영체제 정보를 저장하였습니다.그후 getopt루프문을 통하여 각 옵션 입력시 에 해당 옵션으로 동작하도록 하였습니다.

uts,sysinfo,sysconf함수 출력부분을 따로 void형 함수로 만들어서 출력해주었습니다. m,n,r,s 는 uts구조체의 각 멤버에 접근하여 정보를 출력해주었습니다.

getdelim_file함수를 이용한 출력은 후에 함수설명쪽에서 설명하겠습니다.

출력함수부분입니다. sys/utsname.h 헤더에 정의되어있는 utsname구조체 uts 를 선언하여 uname함수를 호출하 고 uts구조체에 저장하여 출력하는식으로 os이름,

노드이름, 릴리즈번호, 버전, 머신 멤버를 출력하였습니다. sys/sysinfo.h 헤더에 정의되어있는 sysinfo구조체 sys를 선언하여

sysinfo함수를 호출하고 정보를 sys구조체에 저 장하여 출력해주었습니다. 이부분에서 lily는 linux기반의 cent os이기에 유닉스의 sysinfo함수와는 조금 다르기에

man sysinfo를 통해 사용 매뉴얼을 확인해주었습니다. 각 구조체가 long, unsigned long, unsigned short로 정의 되어있어서

%ld, %lu, %hd로 출력해주었습니다. sysconf함수를 사용하여 시스템의 자원정보를 출력해주었습니다.

이함수는 파일경로를 받아서 해당 파일을 출력해주는 함수입니다. getdelim함수를 사용하여 구분자단위로 잘라내 어 출력하였습니다.

getdelim함수를 사용하면 버퍼메모리가 부족할 경우 알아서 realloc을 호출하여 버퍼크기를 늘 려주기 때문에

메모리할당, 재할당, 오버플로우 체크등의 작업을 하지 않아도 된다는점이 장점입니다. /proc디렉토 리의 출력에 사용하려는 파일들은 0을 구분자로 사용하기 때문에

getline으로 출력하게되면 개행문자가 두 번 출력 됩니다. 따라서 해당 디렉토리의 파일들은 delim에 0을 할당하여 사용해주었고

나머지는 getline처럼 사용되면 되 기 때문에 구분자로 \n을 할당하여 사용해주었습니다. 후에 free함수로 메모리를 해제해주었습니다.

따로 옵션을 선택하여 정보를 출력할 때 os의 정보등을 출력하기위해서 함수와 시스템콜등을 찾아보았는데 uts구 조체를 사용하여

출력하는 간단한 정보정도밖에 출력되지않아 어떻게하면 좀더 세부적인 내용을 출력할 수 있을까 생각해보았습니다.

그러던중 유닉스 디렉토리의 구성을 보면 /etc는 시스템 환경설정 디렉토리, /proc은 커널과 프 로세스를 위한 파일시스템 디렉토리임을 확인하게되었고

이 디렉토리를 찾아보니 해당 내용들을 확인 할 수 있었 습니다.

커널버전 proc/version, 배포판 버전확인 /etc/redhat-release, 메모리정보확인 /proc/meminfo, 운영체제 정보 /etc/os-release 등등...을

cat명령어로 찾아보니 조금더 디테일한 내용을 확인 할 수 있었습니다. 확인한 파일들 메인에서 경로를 받아 a,o,r,v,c옵션을 사용할 때 출력해주었습니다.


-a옵션

all옵션입니다. c옵션만 파일의 길이가 길기 때문에 제외하고 모두 출력해주었습니다.

-u옵션

utsname구조체의 sysname, nodename, release, version, machine을 출력해주었습니다.

-i옵션

sysinfo함수를 사용하여 시스템통계정보를 출력해주었습니다.

-f옵션

sysconf함수를 사용하여 시스템자원정보를 출력해주었습니다.

-m옵션

utsname.h헤더에 정의되어있는 utsname 구조체의 machine멤버를 출력해주었습니다. 운영체제가 동작하는 하드웨어의 표준이름(아키텍쳐)입니다.

-n옵션

utsname.h헤더에 정의되어있는 utsname 구조체의 nodename멤버를 출력해주었습니다. 네트워크를 통해 통신할 때 사용하는 시스템의 이름입니다.

-o옵션

운영체제에대한 정보를 출력합니다. /etc/os-release 파일을 getdelim함수를 사용하여 출력해주었습니다.

-r옵션

utsname.h헤더에 정의되어있는 utsname 구조체의 release멤버를 출력해주었습니다. /etc/redhat-release파일을 getdelim함수를 사용하여 출력해주었습니다.

-s옵션

utsname.h헤더에 정의되어있는 utsname 구조체의 sysname멤버를 출력해주었습니다.

-v옵션

운영체제의 버전에 대한 정보를 출력합니다. /proc/version 파일을 getdelim함수를 사용하여 출력해주었습니다.

-c옵션

cpu에 대한 정보를 출력합니다. /proc/cpuinfo 파일을 getdelim함수를 사용하여 출력해주었습니다.