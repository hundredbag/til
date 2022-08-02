# ForestDB의 Asynchronous IO

ForestDB에서 File IO를 담당하는 



### async_io_handle 구조체

```c
struct async_io_handle {
#ifdef _ASYNC_IO
#if !defined(WIN32) && !defined(_WIN32)
    struct iocb **ioq;
    struct io_event *events;
    io_context_t ioctx;
#endif
#endif
    uint8_t *aio_buf;
    uint64_t *offset_array;
    size_t queue_depth;
    size_t block_size;
    int fd;
};
```



## filemgr Operations

Linux 환경의 Operation 들은 `src/filemgr_ops_linux.cc`,
Windows 환경의 Operation 들은 `src/filemgr_ops_windows.cc` 에 정의되어 있음.

그 중 asynchronous I/O operation들은 다음과 같다.

1. **_filemgr_aio_init**
2. **_filemgr_aio_prep_read**
3. **_filemgr_aio_submit**
4. **_filemgr_aio_getevents**
5. **_filemgr_aio_destroy,**






문제상황 : submit이 queue_depth보다 적은 수가 제출된 경우부터 에러가 발생하기 시작.

1. Submit 이전, 이후 SQ ring, CQ ring 상태 확인

2. 1의 결과가 정상적인 경우 - Submit 수가 queue_depth 보다 적은 경우 noop 으로 나머지를 채운 뒤 submit 하도록 수정.

3. get event 수행 후 noop으로 채운 버전에서 오류가 발생하는지 확인할 것.

잘되는것으로 보입니다. 헤ㅏ하하먼에히ㅏㅁ넝하