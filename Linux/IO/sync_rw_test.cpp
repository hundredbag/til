#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <fcntl.h>

#define SECTOR_SIZE 512
#define BLOCK_SIZE 4096

void *data;

int main(int argc, char *argv[]){
	int rfd, wfd;

	posix_memalign(&data, SECTOR_SIZE, BLOCK_SIZE);

	if (rfd = open("./testfile", O_RDONLY | O_DIRECT)) {
		printf("file rfd open succeeded\n");
	} else {
		printf("file rfd open failed\n");
	}

	if (wfd = open("./write_test-sync", O_RDWR | O_DIRECT | O_CREAT, 0666)) {
		printf("file wfd open succeeded\n");
	} else {
		printf("file wfd open failed\n");
	}

	int read_count = pread(rfd, data, BLOCK_SIZE, 0);
	//int read_count = pread(rfd, data, 1024, 0);
	printf("Read count : %d\n", read_count);
	puts((char *)data);
	int write_count = pwrite(wfd, data, BLOCK_SIZE, 0);
	printf("Write count : %d\n", write_count);


	close(rfd);
	close(wfd);
	return 0;
}
