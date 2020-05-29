## GitHub Desktop 사용

GitHub Desktop은 GUI를 이용해서 Git, GitHub를 이용할 수 있도록 해주는 프로그램



### 1. 설치

<https://desktop.github.com/>

위 링크에서 알맞은 설치파일을 다운받은 뒤 설치



### 2. Repository Clone

***1) Github 홈페이지에서 클론하기***

a. Repository 에서 **"Clone or download"** 클릭 후 현재 Repository의 주소 복사 

b. GitHub Desktop 프로그램에서 "File > Clone a repository" 클릭 후 Repository를 Clone



### 3. Commit and Push

***1) Commit***

a. **현재 branch 확인** 및 **Fetch origin**  클릭하여 서버와 현재 로컬 상태를 동기화

b. **Chages** 에서 초록 부분은 추가된 것, 빨간 부분은 삭제된 것을 의미

c. 왼쪽 아래에 commit message(필수)와 description(옵션) 작성 후 **Commit to $branch_name** 버튼 클릭

이 단계는 로컬에서 커밋하는 것이며, 아직 서버에는 변경이 적용되지 않은 상태



***2) Push***

Commit 한 내용을 GitHub 서버에 업로드하는 것

Commit 후 상단 오른쪽 버튼이 Push origin 으로 변경되었으면, 해당 버튼 클릭하여 Push 할 수 있음