#  Install ForestDB-Benchmark

> 본 문서는 Ubuntu 기반으로 작성되었음
>
> reference : <https://github.com/couchbaselabs/ForestDB-Benchmark/blob/master/INSTALL.md>

### Compilation and Build

- Compile 과정에서 Cmake 를 이용하기 때문에 설치해야함 (Cmake version 3.1)

  `sudo apt-get install cmake`

- Cmake 설치 후에 아래 순서에 따라 compile, build를 수행

  ```shell
  git clone [ForestDB-Benchmark_repo_url]
  cd ForestDB-Benchmark
  mkdir build
  cd build
  cmake ../

  ForestDB_BASE=/home/baek/forestdb-1.0/

  export LD_LIBRARY_PATH=$ForestDB_BASE/build

  cmake -DCMAKE_INCLUDE_PATH=$ForestDB_BASE/include -DCMAKE_LIBRARY_PATH=$ForestDB_BASE/build ../ 

  make fdb_bench
  ```




### Trouble shooting

- cmake 명령 수행할 때 `-DCMAKE_INCLUDE_PATH=$ForestDB_BASE/include` 옵션 추가
- cmake 명령 수행할 때 `-DCMAKE_LIBRARY_PATH=$ForestDB_BASE/build` 옵션 추가
- `export LD_LIBRARY_PATH=$ForestDB_BASE/build` 를 통해 라이브러리 경로 지정
- `block_reusing_threshold` 변수가 정의되지 않았다는 에러 발생 => 해당 line 제거해도 benchmark 동작함.

  ```
g++ -g -Wall -O0 compaction_test.cc -I ~/fdb_test/forestdb-1.0-libaio/include/ -L ~/fdb_test/forestdb-1.0-libaio/build/ -lforestdb
  ```