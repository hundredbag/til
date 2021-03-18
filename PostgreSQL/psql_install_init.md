# PostgreSQL 9.3.4 install & init

### 1. 계정 생성 및 로그인

```bash
$ adduser postgres
$ su - postgres
```

### 2. 소스코드 다운로드

- 알맞은 버전의 PostgreSQL을 다운로드 (이 문서에서는 9.3.4 버전의 tar.gz 코드를 사용)
    - [https://www.postgresql.org/ftp/source/](https://www.postgresql.org/ftp/source/)
- 또는 간단히 다음 명령을 수행 후 압축 해제

    ```bash
    wget https://ftp.postgresql.org/pub/source/v9.3.4/postgresql-9.3.4.tar.gz
    tar xvzf postgresql-9.3.4.tar.gz
    cd postgresql-9.3.4.tar.gz
    ```

### 3. Dependencies

- INSTALL 파일 확인

### 4. Configure

```bash
./configure --prefix=/home/postgres/pgsql --with-blocksize=4 --enable-debug
```

- `--prefix` 는 PostgreSQL 설치 디렉토리

### 5. Build and Install

```bash
make -j8
make install
```

- prefix 위치에 파일들이 적절히 생성되었으면 성공

### 6. Database init

```bash
# db initialize
$ initdb -D /home/postgres/pgsql/data

# database server start
$ pg_ctl -D /home/postgres/pgsql/data -l /home/postgres/pgsql/logfile start

# database server status check
$ pg_ctl status -D pgsql/data/
pg_ctl: server is running (PID: 17107)
/home/postgres/pgsql/bin/postgres "-D" "pgsql/data"

# connect DB using psql (command-line interface)
$ psql 

# psql command example
$ psql -U [user_name] -d [database_name]
```