# gcc

> 출처 : <http://doc.kldp.org/KoreanDoc/html/gcc_and_make/gcc_and_make.html#toc3>

gcc 는 GNU 프로젝트에서 만들어진 C 컴파일러



## gcc 사용하기

```c
#include <stdio.h>
int main ( void )
{
  printf ( "Hello world!\n");
  return 0;
}
```

`gcc hello.c` 명령을 수행하면 `a.out` 이라는 이름의 실행 파일이 생성됨



### -o 옵션

* output file 이름을 정하는 옵션
* `gcc -o hello hello.c` / `gcc hello.c -o hello` 두 가지 모두 가능 (실행 파일 이름 : `hello`)



### -c 옵션

* compile 만 수행하는 옵션 (object file 을 생성)

* foo.c, bar.c 두 파일로 구성되는 프로그램의 경우

  ```shell
  방법 (1)
  $ gcc -o hello foo.c bar.c
  -------------------------------------------
  방법 (2)
  $ gcc -c foo.c bar.c
  $ gcc -o baz foo.o bar.o
               ^^^^^^^^^^^
  ```

  > 컴파일	: .c 파일 ==> .o 파일
  >
  > 링크	: .o 파일 ==> 실행 파일



### -I 옵션 (i의 대문자)

* `#include` 문장에서 지정한 헤더 파일의 경로를 정하는 옵션

* ```c
  #include <stdio.h>
  #include "my_header.h"
  ```

  * `<stdio.h>` 의 경우 시스템 표준 헤더 디렉토리인 `/usr/include` 를 기준으로 파일을 찾아 포함시킴
  * `"my_header.h"` 의 경우 컴파일러가 실행되고 있는 현재 디렉토리를 기준으로 헤더 파일을 찾음
  * 이 두 디렉토리가 아닌 곳에 대해서는 명시적으로 `-I<디렉토리>` 로 지정해줘야함 

* ```
   $ gcc -c myprog1.c -I..
   $ gcc -c myprog1.c -Iinclude
   ```

     * 첫번째 : 헤더 파일이 현재 소스 하위 디렉토리(..)에 있다는 뜻
     * 두번째 : 헤더 파일이 현재 디렉토리의 include라는 디렉토리에 들어있다는 뜻



### -l 옵션과 -L 옵션 (둘 다 L)

* -l 옵션 (소문자 L)

  * 링크 할 라이브러리를 명시해주는 옵션
  * `libmylib.a` 라는 라이브러리를 사용하기 위해서는 `-lmylib` 이라는 옵션을 줘야함
  * `libaio.a` 라이브러리 사용 시 `-laio` 옵션을 줘야함

* -L 옵션

  * `-L` 옵션은 라이브러리가 있는 위치를 지정해주는 명령
  * ld 는 유닉스에서 사용되는 Linker

* 라이브러리

  * 반복적으로 사용하게 되는 함수들을 어디에서든 유용하게 사용할 수 있도록 합니다.

  * `.a` 의 확장자

    * ex) `/usr/lib` 디렉토리에 많은 라이브러리들이 있음

      ```
      libaio.a
      libanl.a
      libBrokenLocale.a
      libc.a
      libcapstone.a
      libc_nonshared.a
      libcrypt.a
      libdl.a
      libdw.a
      libebl.a
      libelf.a
      ...
      ```

  * 라이브러리는 컴파일 과정을 거쳐 만든 `.o` 파일을 모아 관리하는 것 (GNU 명령인 `ar` 을 이용하여 확인가능)

    ```shell
    $ ar t libaio.a 
    io_queue_init.ol
    io_queue_release.ol
    io_queue_wait.ol
    io_queue_run.ol
    io_getevents.ol
    io_submit.ol
    io_cancel.ol
    io_setup.ol
    io_destroy.ol
    raw_syscall.ol
    compat-0_1.ol
    ```

