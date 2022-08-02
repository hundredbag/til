# Install ForestDB

> 본 문서는 Ubuntu 기반으로 작성되었음
> reference : <https://github.com/couchbase/forestdb/blob/master/INSTALL.md>

### Dependency

1. ForestDB의 compress option 중 Snappy 를 이용하는 옵션이 있기 때문에 Snappy library를 설치

   `sudo apt-get install libsnappy-dev`

2. Asynchronous IO library 인 `libaio` 를 설치 (compaction 시 `libaio`를 사용하여 여러 IO를 한번에 요청)

   `sudo apt-get install libaio-dev`


### Compilation and Build

- Compile 과정에서 Cmake 를 이용하기 때문에 설치해야함 (Cmake version 3.1)

  `sudo apt-get install cmake`

- Cmake 설치 후에 아래 순서에 따라 compile, build를 수행

  ```shell
  git clone git://github.com/couchbase/forestdb
  cd forestdb
  mkdir build
  cd build
  cmake ../
  make all
  ```



### Test

- Run all the unit tests

  `make test`