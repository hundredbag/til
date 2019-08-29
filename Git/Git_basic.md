# Git - Getting started





### 1. Local 에서 repository 만들어서 시작

- 현재 디렉토리를 버전 저장소로 만들기

  ```shell
  git init
  ```

- .git 디렉토리

  - 버전관리 관련 정보를 저장하는 디렉토리

    ​


### 2. Github에서 repository 가져와서 시작









---

### 3. git이 관리할 대상으로 파일 등록

- git은 기본적으로 새로운 파일을 관리하지 않는다.
  (프로젝트의 임시 파일 등 관리하지 않는 파일을 추적하지 않기 위해)

- 파일을 관리하기 위해서는 파일을 관리 대상으로 등록해야한다.

- git add 를 통해 파일을 추적하도록 명령

  - ​

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