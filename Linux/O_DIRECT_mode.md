# Linux file access - O_DIRECT mode

<https://www.ibm.com/support/knowledgecenter/en/STXKQY_4.2.3/com.ibm.spectrum.scale.v4r23.doc/bl1adm_considerations_direct_io.htm>



When a file is opened in the O_DIRECT mode (direct I/O mode), GPFS™ transfers data directly between the user buffer and the file on the disk.

- The file is accessed at random locations.
- There is no access locality.


- The number of bytes transferred is a multiple of 512 bytes.
- The file offset is a multiple of 512 bytes.
- The user memory buffer address is aligned on a 512-byte boundary.

When these conditions are *not* all true, the operation will still proceed but will be treated more like other normal file I/O, with the O_SYNC flag that flushes the dirty buffer to disk.

When these conditions *are* all true, the GPFS page pool is not used because the data is transferred directly; therefore, an environment in which most of the I/O volume is due to direct I/O (such as in databases) will not benefit from a large page pool. Note, however, that the page pool still needs to be configured with an adequate size, or left at its default value, because the page pool is also used to store file metadata (especially for the indirect blocks required for large files).

With direct I/O, the application is responsible for coordinating access to the file, and neither the overhead nor the protection provided by GPFS locking mechanisms plays a role. In particular, if two threads or nodes perform direct I/O concurrently on overlapping portions of the file, the outcome is undefined. For example, when multiple writes are made to the same file offsets, it is undetermined which of the writes will be on the file when all I/O is completed. In addition, if the file has data replication, it is not guaranteed that all the data replicas will contain the data from the same writer. That is, the contents of each of the replicas could diverge.

- The write causes the file to increase in size.
- The write is in a region of the file that has been preallocated (via gpfs_prealloc()) but has not yet been written.
- The write is in a region of the file where a hole is present; that is, the file is sparse and has some unallocated regions.


- The I/O operation needs to be served by an NSD server.
- The file system has data replication. In the case of a write operation, the GPFS daemon is involved to produce the log records that ensure that the replica contents are identical (in case of a failure while writing the replicas to disk).
- The operation is performed on the Windows operating system.

Note that setting the O_DIRECT flag on an open file with fcntl (fd, F_SETFL,[..]), which may be allowed on Linux, is ignored in a GPFS file system.

 Because of a limitation in Linux, I/O operations with O_DIRECT should not be issued concurrently with a fork(2) system call that is invoked by the same process. Any calls to fork() in the program should be issued only after O_DIRECT I/O operations are completed. That is, fork() should not be invoked while O_DIRECT I/O operations are still pending completion. For more information, see the open(2) system call in the Linux documentation.