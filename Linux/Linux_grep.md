# grep command



  **패턴 검색 [grep]** 

grep 명령은 파일 내에서 지정한 패턴이나 문자열을 찾은 후에, 그 패턴을 포함하고 있는 모든 행을 표준 출력해 준다. 물론, 한 디렉토리 내에서 지정한 패턴을 포함하는 파일을 출력할 수도 있다. grep 명령은 하나 이상의 파일로부터 프로그램 수정 등을 위해 변수, 또는 함수명을 찾을때 많이 사용된다. 

  **grep 명령의 기본 문법** 

**grep [-옵션] 패턴 파일명** 

   **옵션**

**-c :** 패턴이 일치하는 행의 수를 출력 

**-i :** 비교시 대소문자를 구별 안함 

**-v :** 지정한 패턴과 일치하지 않는 행만 출력 

**-n :** 행의 번호를 함께 출력 

**-l :** 패턴이 포함된 파일의 이름을 출력 

**-w :** 패턴이 전체 단어와 일치하는 행만 출력 

   **사용 예** 

**$ grep -n '삼성' token_dic**

= token_dic 이라는 파일내에서 '삼성' 이라는 패턴이 들어간 문자열과 행번호를 출력 

![img](https://t1.daumcdn.net/cfile/tistory/1323FF394FBC3B6F10)

**$grep -l '삼성' \*** 

= 현재 디렉토리의 모든 파일에서 '삼성' 이라는 패턴이 들어간 파일의 이름을 출력 

![img](https://t1.daumcdn.net/cfile/tistory/16599B464FBC3C9705)

**$grep -v '삼성' \*** 

= 현재 디렉토리의 모든 파일에서 '삼성' 이라는 패턴이 들어가지 않은 행을 출력

**$grep -r '삼성' \*** 

= 현재 디렉토리 및 서브디렉토리의 모든 파일에서 '삼성' 이라는 패턴이 들어간 문자열 출력

  **패턴의 정규 표현식(Regular Expression)** 

패턴 지정에서 사용되는 정규 표현식은 작은 따옴표 (' ')로 묶어서 표현한다. 

$ grep '^a' 파일명 

= ^는 파일의 시작을 나타냄. 파일에서 a로 시작하는 행을 찾는다. 

$ grep 'apple$' 파일명

= $는 파일의 끝을 나타냄. 파일에서 e로 끝나는 행을 찾는다. 

$ grep 'app*' 파일명 

= 파일에서 app로 시작하는 모든 단어를 찾는다. 

$ grep 'a.....e' 파일명 

= 파일에서 a로 시작하고 e로 끝나는 7자리 단어를 찾는다. 

$ grep [a-d] 파일명 

= 파일에서 a,b,c,d 로 시작하는 단어를 모두 찾는다. 

$ grep [aA]pple 파일명 

= 파일에서 apple 또는 Apple로 시작하는 단어를 모두 찾는다.

$ grep 'apple' d*

= d로 시작하는 모든 파일에서 apple 를 포함하는 모든 행을 찾는다. 

$ grep 'apple' 파일명1 파일명2 

= 지정된 두개의 파일에서 apple 를 포함하는 모든 행을 찾는다. 

$ grep '^[ab]' 파일명 

= 파일에서 a나 b로 시작되는 모든 행을 찾는다. 

출처: 

https://ra2kstar.tistory.com/100

 [초보개발자 이야기.]

출처: 

https://ra2kstar.tistory.com/100

 [초보개발자 이야기.]