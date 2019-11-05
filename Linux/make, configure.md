# configure and make



대충 :D 맞습니다.

autotool을 기준으로 설명드리자면,

configure 는 shell script 로써, 주로 시스템 의존적인 요소들을 직접 컴파일이나 링크등을 통하여 테스트함으로써 config.status 를 만들어 주는 일을 합니다.

config.status 는 Makefile.in 이라는 파일에서 Makefile 을 만드는데 사용됩니다. 이때, Makefile.in 내의 @VARIABLE@ 형태로 되어 있는 것을 시스템 의존적인 것으로 치환하여 만드는 일을 합니다.

make는 Makefile 을 읽어서 차례대로 object나 library, 실행 파일을 만드는일을 하지요.

make install 은 실행파일이나 라이브러리등을 시스템에 설치하는데 사용합니다.

make clean 은 중간파일과 최종 파일(실행파일, 라이브러리)들을 제거하는데 사용합니다.

그 밖에

make dist 는 배포소스를 만드는데 사용합니다.

make check 는 test 하는데 사용합니다.

수고하세요..



나중에 Make 내용 정리 (책 참고) 할것.