# mmap(), munmap(), msync()

## 메모리 맵

mmap(2) 이란 메모리의 내용을 파일이나 디바이스에 대응(mapping)하기 위해 사용하는 시스템 호출이다.



### 2.1. 메모리 관리와 mmap

각각의 프로세스는 다른 프로세스와는 중복되지 않는 주소공간을 가지게 됨.

프로세스 메모리는 기본적으로 다른 프로세스와 공유되지 않기 때문에, 다른 프로세스와 특정 데이터를 공유하기 위해 IPC를 사용하게 된다.

mmap은 메모리의 특정 영역을 파일로 대응시킬 수 있도록 도와준다. 파일은 시스템 전역적인 객체이므로 다른 프로세스에서 접근 가능하도록 할 수 있으며, 이러한 mmap의 특징때문에 IPC 용도로 사용 가능하다 (mmap이 IPC 용도로 사용 가능하지만 IPC 설비는 아님)

mmap은 프로세스의 주소 공간을 파일에 대응시킨다.



### 2.2 mmap의 활용 용도

메모리의 내용을 파일에 대응시킴으로써 발생하는 장점

1. 메모리의 내용을 파일에 대응시켜 프로세스 간 데이터 교환의 용도로 활용 가능. 프로세스간 공유하고자 하는 데이터를 파일에 대응시키고 이것을 읽고 쓰면 된다. (접근 제어가 추가적으로 필요하긴 함)
2. 고전적인 open, read, write, seek에 비해 성능 향상을 기대할 수 있음 (자세한 내용은 후술)



### 2.3. mmap 설명

mmap의 definition

```c
#include <sys/mman.h>

#ifdef _POSIX_MAPPED_FILES
void * mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);

int munmap(void *start, size_t length);
#endif
```

mmap 함수는 start 부터 length까지의 메모리 영역을 열린 파일 fd에 대응한다. 대응할 때 파일의 위치를 지정할 수 있는데 이것은 offset을 통해 이루어진다.

prot은 파일에 대응되는 메모리 영역의 보호특성을 결정하기 위해 사용된다. 메모리 영역과 파일이 서로 대응되기 때문에 파일에 대한 작업이 메모리 영역에 직접적인 영향을 줄 수 있기 때문이다. prot은 다음과 같은 flag들을 제공한다.

- PROT_EXEC : 페이지는 실행될 수 있다.
- PROT_READ : 페이지는 읽혀질 수 있다.
- PROT_WRITE : 페이지는 쓰여질 수 있다.
- PROT_NONE : 페이지에 접근할 수 없다.

flags는 대응되는 객체의 형식(type)을 지정하기 위해 사용된다. flags 값에 따라 대응된 페이지를 다른 프로세스와 공유할 것인지, 생성한 프로세스만 사용할 수 있는지를 지정할 수 있다.

- MAP_FIXED
- MAP_SHARED
  - 대응되는 객체를 다른 프로세스도 공유할 수 있도록 함. 프로세스들은 객체에 대해 동등한 권한을 가지게 되며, 객체 접근에 대한 동기화를 위해 msync(2)와 munmap(2)가 사용된다.
- MAP_PRIVATE

mmap을 사용할 때에는 반드시 MAP_PRIVATE 또는 MAP_SHARED를 사용해야 한다.



## 3. Example 1

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    char *file = NULL;
    struct stat sb;
    char buf[80] ={0x00,};
    int flag = PROT_WRITE | PROT_READ;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: input\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR | O_CREAT)) < 0)
    {
        perror("File Open Error");
        exit(1);
    }

    if (fstat(fd, &sb) < 0)
    {
        perror("fstat error");
        exit(1);
    }

    file = (char *) mmap(0, 40, flag, MAP_SHARED, fd, 0);
    if (file == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }   
    printf("%s\n", file);
    memset(file, 0x00, 40);
    
    //msync(file, 40, MS_SYNC);
    //munmap(file, 40);
    
    close(fd);
    return 0;
}   

```



## 4. mmap을 이용한 프로세스간 데이터 공유

