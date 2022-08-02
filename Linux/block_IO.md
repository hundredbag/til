# Block I/O architecture

**Block device**는 개별 바이트 단위가 아니라 **일정 크기(Block) 단위로 데이터에 접근**하는 장치를 일컫는다 
(e.g. 하드디스크, SSD ...)

* Block Device는 파일 시스템이라는 추상화 계층을 통해 간접적으로 접근됨
* 프로그래머는 저장장치의 종류와 관계 없이 일관된 방식(파일 및 디렉토리의 형태)으로 이용 가능
  (VFS 에 의해 어떠한 파일 시스템인지와도 무관하게)
* Block device는 CPU, memory 에 비해 매우 느림
  (SSD의 경우 HDD에 비해 상대적으로 빠르지만 여전히 CPU, memory에 비해 느림)
* VFS 계층은 페이지 캐시를 이용하여 접근되었던 디스크의 내용을 저장해둔다.



Block I/O의 시작 지점은 `submit_bio()` 함수

`submit_bio()` 함수는 I/O 연산의 종류(read/write) 및 연산에 대한 정보를 포함하느 `bio` 구조체를 인자로 받음