# PostgreSQL에서 TPC-H 사용하기

## 1. TPC-H 다운로드 및 설치

1. TPC-H Tools 다운로드 : http://www.tpc.org/default.asp
2. unzip tpch-tools.zip
3. tpch-tools 디렉토리에 dbgen, dev-tools, ref-data 3개의 디렉토리 확인
4. dbgen 디렉토리에서 Makefile 생성 (makefile.suite 이용

   ```shell
    cp makefile.suite Makefile
   ```

5. Makefile에 환경설정 값 기입

        CC = gcc
        DATABASE = ORACLE 
        MACHINE = LINUX 
        WORKLOAD = TPCH

6. make
7. dbgen 명령으로 data 생성

        ./dbgen -s 10 # 숫자 1은 약 1GB

8. Oracle-like CSV 파일들이 생성 완료

    ( customer.tbl lineitem.tbl nation.tbl orders.tbl partsupp.tbl part.tbl region.tbl supplier.tbl )



## 2. PostgreSQL에서 TPC-H 수행하기

reference : https://github.com/tvondra/pg_tpch

- Oracle-like CSV 파일을 PostgreSQL에 알맞은 CSV 파일의 형태로 변환해야함

    ```shell
    $ for i in `ls *.tbl`; do sed 's/|$//' $i > ${i/tbl/csv}; echo $i; done;
    ```

    ( *.tbl 파일의 각 row의 마지막 | 문자를 제거한 뒤, 확장자를 csv로 변환하는 명령어 )


- Query 생성

    pg_tpch/dss dir을 dbgen dir로 이동 후, dbgen/queries dir을 dbgen/dss/로 이동

    ```shell
    git clone https://github.com/tvondra/pg_tpch.git

    cp -r ~/pg_tpch/dss ~/tpch/dbgen/
    cp -r ~/tpch/dbgen/queries ~/tpch/dbgen/dss/

    for q in `seq 1 22`
    do
        DSS_QUERY=dss/templates ./qgen $q >> dss/queries/$q.sql
        sed 's/^select/explain select/' dss/queries/$q.sql > dss/queries/$q.explain.sql
        cat dss/queries/$q.sql >> dss/queries/$q.explain.sql;
    done
    ```

- 이것을 완료하면 1.sql 1.explain.sql 2.sql … 등등의 파일이 생성되는데, 파일을 열어보면 ^M (아스키 코드 13번 CR)이 뒤에 다 붙어있다.

- 이것을 한번에 제거하기 위해, 다음 스크립트를 수행한다.

    ```shell
    #!/bin/bash

    for dir in $(ls *.sql);
    do
      echo "$dir";
      sed -i s/^M//g $dir  # ^M은 Control + v + m 으로 입력 가능
    done
    ```

- dss 디렉토리의 tpch-load.sql의 COPY script 내용 중 파일 경로 부분을 csv 파일이 있는 절대경로로 수정한다.

- 마지막으로, dss 디렉토리의 스크립트를 다음 순서로 실행시킨다.
    1. tpch-load.sql
    2. tpch-pkeys.sql
    3. tpch-alter.sql
    4. tpch-index.sql

    * psql 에서 SQL 파일을 실행하는 방법 : `\i [실행하고자 하는 파일명]`

- 임시 데이터를 다른 저장장치에 저장하고 싶으면, database 경로의 base dir 안의 pgsql_tmp dir에 장치를 mount 해서 사용하면 된다.



### TPC-H 특징

> http://hundredbag.tistory.com/entry/PostgreSQL%EC%97%90%EC%84%9C-TPCH-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0?category=997133