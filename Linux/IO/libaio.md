# libaio

## iocb (I/O control block) structure

* Defined : `linux/aio_abi.h`

* ```c
  struct iocb {
      __u64   aio_data;
      __u32   PADDED(aio_key, aio_rw_flags);
      __u16   aio_lio_opcode;
      __s16   aio_reqprio;
      __u32   aio_fildes;
      __u64   aio_buf;
      __u64   aio_nbytes;
      __s64   aio_offset;
      __u64   aio_reserved2;
      __u32   aio_flags;
      __u32   aio_resfd;
  };
  ```



## io_prep_{pread, pwrite, preadv, pwritev}

* Defined : `libaio.h`

* <https://code.woboq.org/linux/include/libaio.h.html#25iocb>

* ```c
  static inline void io_prep_pread(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
  {
  	memset(iocb, 0, sizeof(*iocb));
  	iocb->aio_fildes = fd;
  	iocb->aio_lio_opcode = IO_CMD_PREAD;
  	iocb->aio_reqprio = 0;
  	iocb->u.c.buf = buf;
  	iocb->u.c.nbytes = count;
  	iocb->u.c.offset = offset;
  }
  static inline void io_prep_pwrite(struct iocb *iocb, int fd, void *buf, size_t count, long long offset)
  {
  	memset(iocb, 0, sizeof(*iocb));
  	iocb->aio_fildes = fd;
  	iocb->aio_lio_opcode = IO_CMD_PWRITE;
  	iocb->aio_reqprio = 0;
  	iocb->u.c.buf = buf;
  	iocb->u.c.nbytes = count;
  	iocb->u.c.offset = offset;
  }
  static inline void io_prep_preadv(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset)
  {
  	memset(iocb, 0, sizeof(*iocb));
  	iocb->aio_fildes = fd;
  	iocb->aio_lio_opcode = IO_CMD_PREADV;
  	iocb->aio_reqprio = 0;
  	iocb->u.c.buf = (void *)iov;
  	iocb->u.c.nbytes = iovcnt;
  	iocb->u.c.offset = offset;
  }
  static inline void io_prep_pwritev(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset)
  {
  	memset(iocb, 0, sizeof(*iocb));
  	iocb->aio_fildes = fd;
  	iocb->aio_lio_opcode = IO_CMD_PWRITEV;
  	iocb->aio_reqprio = 0;
  	iocb->u.c.buf = (void *)iov;
  	iocb->u.c.nbytes = iovcnt;
  	iocb->u.c.offset = offset;
  }
  ```

* ​kring_entries 의 숫자가 세팅이 안되어있는 것이 문제임.