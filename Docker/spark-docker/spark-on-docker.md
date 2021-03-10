# Running Spark on Docker

## Docker 이미지 다운로드, 컨테이너 실행

1. Spark 도커 이미지 파일 다운로드
([https://hub.docker.com/repository/docker/hundredbag/spark-docker/general](https://hub.docker.com/repository/docker/hundredbag/spark-docker/general))

    ```bash
    docker pull hundredbag/spark-docker:1.0
    ```

2. Container 실행 (-v 옵션에는 hadoop에서 사용할 directory를 지정)

    ```bash
    docker run -it -h hadoopmaster --name sparkdocker \
    -p 50070:50070 \
    -p 8088:8088 \
    -v [host_hdfs_directory]:/root/hadoopdata/hdfs \
    -v [host_tmp_directory]:/root/hadoopdata/tmp \
    hundredbag/spark-docker:1.0

    ex)
    docker run -it -h hadoopmaster --name sparkdocker \
    -p 50070:50070 \
    -p 8088:8088 \
    -v /root/hadoopdata/hdfs:/root/hadoopdata/hdfs \
    -v /root/hadoopdata/tmp:/root/hadoopdata/tmp \
    hundredbag/spark-docker:1.0

    ```



## Hadoop 실행 & Benchmark 실행

아래 명령들은 docker container 내에서 실행되는 내용임.

1. Hadoop, Yarn 실행

    ```bash
    cd ~/
    ./hdfs_reset.sh
    hdfs namenode -format
    start-all.sh
    ```

    **정상적인 동작을 위해 확인해야할 내용**

    - `jps` 명령을 실행했을 때 NameNode, DataNode, SecondaryNameNode, ResourceManager, NodeManager가 실행 중
    - `hdfs dfsadmin -report` 명령을 실행해서 Live datanode가 정상적으로 나타남

2. 벤치마크 수행

    ```bash
    cd ~/HiBench

    # Prepare to run
    ./bin/workloads/micro/sort/prepare/prepare.sh

    # Run Benchmark
    ./bin/workloads/micro/sort/spark/run.sh
    ```

3. 결과 확인 : `~/HiBench/report` 디렉토리의 `hibench.report` 파일 확인



## Benchmark configuration details

### Dataset size 변경

- `~/HiBench/conf/hibench.conf` 파일의 `hibench.scale.profile` 항목을 변경하여 수정 가능
    - tiny, small, large, huge, gigantic, bigdata 수준 중 선택
    - 구체적인 datasize 변경을 원할 시 `~/HiBench/conf/workloads` 디렉토리에서 수정 가능

### 병렬성 정도 변경

아래 내용을 모두 적용해야 함.

- `~/HiBench/conf/hibench.conf` 파일의 `hibench.default.map.parallelism`,  `hibench.default.shuffle.parallelism` 항목을 변경
- `~/HiBench/conf/spark.conf` 파일의 `hibench.yarn.executor.num` 항목과 `hibench.yarn.executor.cores` 항목 변경
- `~/hadoop/etc/hadoop/yarn-site.xml` 파일의 Node manager setting 변경



## Trouble shooting

### Network 문제 발생 시

1. SSH 데몬이 정상적으로 실행중인지 확인
2. Docker container의 IP 주소와 container 내의 ubuntu의 `/etc/hosts` 파일의 IP 주소가 동일한지 확인

    ```bash
    # Docker container IP 주소 확인 명령 (Host에서)
    docker inspect [CONTAINER_ID or CONTAINER_NAME] | grep "IPAddress"
    ```

...