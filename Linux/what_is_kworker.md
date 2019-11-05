# What is kworker process

I learned from [here](https://askubuntu.com/questions/33640/kworker-what-is-it-and-why-is-it-hogging-so-much-cpu)

"kworker" is a placeholder process for kernel worker threads, which perform most of the actual processing for the kernel, especially in cases where there are interrupts, timers, I/O, etc.





페이지 캐시의 dirty page들은 storage에 쓰여져서 clean page가 되어야 해제될 수 있으며, 이 페이지들은 kworker라는 쓰레드에 의해 스토리지에 쓰여진다. kworker 쓰레드는 sleep 상태에 있다가 주기적으로 깨어나서 dirty 페이지들을 스토리지에 쓴다. [논문 참고](http://www.esos.hanyang.ac.kr/files/publication/conferences/korean/WC_ojt.pdf)



근데 read 에서 kworker가 하는 일은?



---



libaio 사용할 때 

예제

<https://stackoverflow.com/questions/15605553/read-file-using-libaio-with-o-direct-flag>

when using O_DIRECT you must match the physical block size or its multiple on the device when issuing read() syscalls. If you are using 1024 in your program , the block size must be 512 bytes, check that. – [Nulik](https://stackoverflow.com/users/922445/nulik) [Apr 7 '13](https://stackoverflow.com/questions/15605553/read-file-using-libaio-with-o-direct-flag#comment22589749_15605553)



You need to align the buffer to 512 bytes for O_DIRECT to work correctly. Before `io_prep_pread`:

```
char *data;
posix_memalign(&data, 512, 1024);
```

Note that the size read has to be a multiple of 512.



---

libaio and O_DIRECT 관계

<https://stackoverflow.com/questions/8768083/difference-between-posix-aio-and-libaio-on-linux>



---

blktrace 에서 +1은 512 byte를 의미한다.

따라서 128K의 write를 요청하는 경우 256을 쓰는 것을 요청한 것으로 측정됨

- D   WS  **0 + 256** [kworker/36:1H]





`sudo btrace /dev/sda | grep -E "[DC]  [WR]|[DC]   [WR]"`