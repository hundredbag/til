# Git intall & setting

### Git install
- git 공식 홈페이지 : https://git-scm.com/

- Windows
  - 공식 홈페이지에서 git 설치 파일을 다운로드 후 실행하여 설치
  - Git bash 프로그램을 실행
  - ```git``` 명령의 결과로 git 사용 방법에 관한 안내가 나타나면 정상적으로 설치 된것임.

- Linux
  - 기본적으로 설치되어 있는 경우가 많음
  - 설치되지 않은 경우 운영체제에 따라 ```sudo apt-get install git``` 또는 ```sudo yum install git``` 을 수행하여 설치




### Git 최초 설정

  - **사용자 정보**

    사용자 이름과 이메일을 git에 등록해줘야 함 (global 옵션은 최초 1번만 설정해주면 됨)

    이 정보는 커밋할 때마다 이용되고, 한번 커밋한 후에는 변경이 불가능함

    ```shell
    $ git config --global user.name "이름"
    $ git config --global user.email abc@example.com
    ```

  - **편집기 (필수 X)**

    Git에서 사용할 텍스트 편집기를 설정 (기본적으로 시스템의 기본 편집기를 이용)

    ```shell
    $ git config --global core.editor emacs
    ```

  - **Diff 도구 (필수 X)**

    Merge 충돌을 해결하기 위해 사용하는 Diff 도구 설정

    ```shell
    $ git config --global merge.tool vimdiff
    ```

  - **설정 확인**

    `git config --list` 명령을 실행하여 설정 확인 가능 (같은 키가 중복된 경우 나중 값을 사용)

    ``` git config <key>``` 명령으로 특정 Key 의 값을 확인 가능

    ​



### 

