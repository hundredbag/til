# fio (Flexible I/O tester)

> <https://fio.readthedocs.io/en/latest/fio_doc.html>

## 1. 소개

- 디스크 성능 측정 프로그램
  - 순차/랜덤 읽기/쓰기 IOPS 측정 등 다양한 측정 가능



## 실행

```
$ fio [options] [jobfile] ...
```

* 사용 방법 1 : 옵션을 command line에서 직접 입력
* 사용 방법 2 : 옵션을 입력해둔 jobfile을 parameter로 전달
  * 하나 이상의 jobfile 전달되면 순서대로 실행함




### Job file 쓰는법

원하는 I/O 워크로드로 fio 테스트를 진행하려면 **Job file** 을 작성해야한다.

* **일반적인 job file 내용**은 **global 섹션**에 공유 파라미터로 정의한다.
* 하나 이상의 **job section 에는 job 내용**을 설정




### I/O 타입

* direct=bool (default : false)

  * True : non-buffered I/O (O_DIRECT 모드)

  > Windows 는 direct I/O를 지원하지 않음

* atomic=bool

  * True : atomic direct I/O를 수행
    * atomic write 는 



### io_engine

* ioengine=*str*

  * io_uring : 최신 리눅스 비동기 IO (kernel 5.1 이후 사용 가능), Direct / Buffered IO 모두 사용 가능

    * sqthread_poll=1 or 0
      * 보통은 fio가 system call을 이용하여 SQ에 아이템이 들어왔음을 커널에 알림
      * sqthread_poll 옵션이 set 되어있으면 submitting IO가 polling 모드로 동작함 (IO 완료를 기다림)

