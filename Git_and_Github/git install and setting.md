## Git intall & setting

## 1. Git 설치

- git 공식 홈페이지 : https://git-scm.com/

- Windows
  - 공식 홈페이지에서 git 설치 파일을 다운로드 후 실행하여 설치
  - Git bash 프로그램을 실행
  - git 명령의 결과로 git 사용 방법에 관한 안내가 나타나면 정상적으로 설치 된것임.

- Linux
  - 기본적으로 설치되어 있는 경우가 많음
  - 설치되지 않은 경우 운영체제에 따라 sudo apt-get install git 또는 sudo yum install git 을 수행하여 설치

  ​

- **Git 최초 설정** 

  - **사용자 정보**
    사용자 이름과 이메일을 git에 등록해줘야 함 (최초 1번만 해주면 됨) 
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

    `git config --list` 명령을 실행하여 설정 확인 가능

    ​



## 2. Git 시작하기

### 2-1. Local 에서 repository 만들어서 시작

- 현재 디렉토리를 버전 저장소로 만들기

  ```shell
  git init
  ```

- .git 디렉토리

  - 버전관리 관련 정보를 저장하는 디렉토리

![1538376663167](C:\Users\my\AppData\Local\Temp\1538376663167.png)

### 2-2. Github에서 repository 가져와서 시작

- ​



### 3. git이 관리할 대상으로 파일 등록

- git은 기본적으로 새로운 파일을 관리하지 않는다.
  (프로젝트의 임시 파일 등 관리하지 않는 파일을 추적하지 않기 위해)

- 파일을 관리하기 위해서는 파일을 관리 대상으로 등록해야한다.

- git add 를 통해 파일을 추적하도록 명령

  - git add 명령 수행 전![1538395181221](C:\Users\my\AppData\Local\Temp\1538395181221.png)

  - git add 명령 수행 후

    ![1538395227150](C:\Users\my\AppData\Local\Temp\1538395227150.png)

    ​


### 4. 버전 만들기 (commit)

- 버전 : 의미 있는 변화
- ​


- git commit 명령을 하면 vim이 켜지고, 여기에 commit message를 입력하고 저장 후 종료(:wq) 함

- commit 및 commit message 내용은 git log를 통해 확인할 수 있음

  ![1538962287986](C:\Users\my\AppData\Local\Temp\1538962287986.png)

- 파일을 수정한 뒤에도 git add를 해주어야 수정된 버전을 추적하도록 할 수 있음

  - git add 전

    ![1538964460142](C:\Users\my\AppData\Local\Temp\1538964460142.png)

  - git add 후

    ![1538964505013](C:\Users\my\AppData\Local\Temp\1538964505013.png)

  - git commit 후

    ![1538964546918](C:\Users\my\AppData\Local\Temp\1538964546918.png)




### 5. Stage area

- 두 개의 파일을 변경한 뒤, 일부의 파일만 add 하여 commit 할 수 있음
  - 즉, commit을 하고자 하는 파일만 골라서 선택적으로 commit 할 수 있음
  - (git add의 대상 파일은 commit 대기 상태가 되는 것임)
  - Git 에서는 commit 대기 상태를 **Stage area** 라고 부름
- Commit 대기 중인 파일이 가는 곳 : **Stage**
- Commit 된 결과가 저장되는 곳 : **Repository**

![1538983231405](C:\Users\my\AppData\Local\Temp\1538983231405.png)



### 6. 변경사항 확인하기

- 지금까지의 commit 기록을 확인하기

  ```shell
  git log
  ```

  ![1539237853970](C:\Users\my\AppData\Local\Temp\1539237853970.png)

- 특정 commit 이전의 기록을 확인하기

  ```shell
  git log $commit_id
  ```

  ![1539242289304](C:\Users\my\AppData\Local\Temp\1539242289304.png)

- 각각의 commit 버전 간의 차이점 확인하기

  ```shell
  git log -p
  ```

  ![1539242143962](C:\Users\my\AppData\Local\Temp\1539242143962.png)

- 특정 두 commit 버전의 차이점 확인하기

  ```shell
  git diff ${commit_id1}..${commit_id2}
  ```

  ![1539245544858](C:\Users\my\AppData\Local\Temp\1539245544858.png)

- git add 하기 전과 add 한 후의 파일 내용을 비교하기

  ```shell
  #git add 후에는 git diff 해도 차이점이 보이지 않는다.
  git diff
  ```



### 7. 과거의 버전으로 돌아가기

