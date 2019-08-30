<<<<<<< HEAD
# Configuring HDFS rack awareness

[원문 : hotronworks - Configuring HDFS rack awareness](https://docs.hortonworks.com/HDPDocuments/HDP3/HDP-3.1.0/data-storage/content/improving_performance_with_hdfs_rack_awareness.html)

The NameNode in an HDFS cluster maintains rack IDs of all the DataNodes. The NameNode uses this information about the distribution of DataNodes among various racks in the cluster to select the closer DataNodes for effective block placement during read/write operations. This concept of selecting the closer DataNodes based on their location in the cluster is termed as rack awareness. Rack awareness helps in maintaining fault tolerance in the event of a failure.



## 1. Create a rack topology script

HDFS는 노드들의 Rack location 정보를 결정하기 위해 executable topology script와 topology data file을 이용한다.

**Steps**

1. Executable topology script 와 topology data file을 생성한다.

   ex) example topology script ```rack-topology.sh```

   ```shell
   #!/bin/bash
   # Adjust/Add the property "net.topology.script.file.name"
   # to core-site.xml with the "absolute" path the this
   # file. ENSURE the file is "executable".

   # Supply appropriate rack prefix
   RACK_PREFIX=default

   # To test, supply a hostname as script input:
   if [ $# -gt 0 ]; then

   CTL_FILE=${CTL_FILE:-"rack_topology.data"}
   HADOOP_CONF=${HADOOP_CONF:-"/etc/hadoop/conf"} 

   if [ ! -f ${HADOOP_CONF}/${CTL_FILE} ]; then
    echo -n "/$RACK_PREFIX/rack "
    exit 0
   fi

   while [ $# -gt 0 ] ; do
    nodeArg=$1
    exec< ${HADOOP_CONF}/${CTL_FILE}
    result=""
    while read line ; do
    ar=( $line )
    if [ "${ar[0]}" = "$nodeArg" ] ; then
    result="${ar[1]}"
    fi
    done
    shift
    if [ -z "$result" ] ; then
    echo -n "/$RACK_PREFIX/rack "
    else
    echo -n "/$RACK_PREFIX/rack_$result "
    fi
   done

   else
    echo -n "/$RACK_PREFIX/rack "
   fi
   ```
   example topology data file ```rack_topology.data```  (hostname으로 사용하면 안되고 반드시 IP를 적을 것)

   ```shell
   # This file should be:
   # - Placed in the /etc/hadoop/conf directory
   # - On the Namenode (and backups IE: HA, Failover, etc)
   # - On the Job Tracker OR Resource Manager (and any Failover JT's/RM's) 
   # This file should be placed in the /etc/hadoop/conf directory.

   # Add Hostnames to this file. Format <host ip> <rack_location>
   192.168.2.10 01
   192.168.2.11 02
   192.168.2.12 03
   ```

2. Topology script 와 data file을 모든 클러스터 노드의 ```/etc/hadoop/conf``` 디렉토리에 복사

3. Topology script를 실행해서 올바른 Rack 정보가 return 되는지 확인

   ```shell
   $./rack-topology.sh 192.168.2.10
   /default/rack_01
   ```



## 2. Add the topology script property to core-site.xml

**Steps**

1. HDFS 클러스터를 중지한다.

2. topology script 파일 정보를 ```core-site.xml``` 에 추가한다.

   ```xml
   <property>
     <name>net.topology.script.file.name</name> 
     <value>/etc/hadoop/conf/rack-topology.sh</value>
   </property>
   ```

   By default, the topology script processes up to 100 requests per invocation. You can specify a number other than the default value with the ```net.topology.script.number.args``` property, as shown in the following example:

   ```xml
   <property> 
     <name>net.topology.script.number.args</name> 
     <value>75</value>
   </property>
   ```

## 3. Restart HDFS and MapReduce services

Topology script 정보를 ```core-site.xml``` 에 추가한 뒤에는 HDFS와 MapReduce 서비스를 재시작해야한다.



## 4. Verify rack awareness

Rack awareness가 동작하는지 확인할 필요가 있다.

**Steps**

1. `/var/log/hadoop/hdfs/` 의 NameNode 로그를 확인한다.

   ```
   014-01-13 15:58:08,495 INFO org.apache.hadoop.net.NetworkTopology: Adding
                           a new node: /rack01/<ipaddress>
   ```

2. `hdfs fsck ` 명령으로 확인 (Number of racks)

   ```
   Status: HEALTHY  
   Total size: 123456789 B  
   Total dirs: 0  
   Total files: 1  
   Total blocks (validated): 1 (avg. block size 123456789 B)
   Minimally replicated blocks: 1 (100.0 %)  
   Over-replicated blocks: 0 (0.0 %)  
   Under-replicated blocks: 0 (0.0 %)  
   Mis-replicated blocks: 0 (0.0 %)
   Default replication factor: 3  
   Average block replication: 3.0  
   Corrupt blocks: 0  
   Missing replicas: 0 (0.0 %)  
   Number of data-nodes: 40  
   Number of racks: 2  
   FSCK ended at Mon Jan 13 17:10:51 UTC 2014 in 1 milliseconds
   ```

3. `hdfs dfsadmin -report` 명령으로 각 데이터노드가 Rack 정보를 가지는지 확인

   ```shell
   Configured Capacity: 19010409390080 (17.29 TB)
   Present Capacity: 18228294160384 (16.58 TB)
   DFS Remaining: 5514620928000 (5.02 TB) DFS
   Used: 12713673232384 (11.56 TB)
   DFS Used%: 69.75%
   Under replicated blocks: 181 
   Blocks with corrupt replicas: 0  
   Missing blocks: 0
   -------------------------------------------------  
   Datanodes available: 5 (5 total, 0 dead)  
   Name: 192.168.90.231:50010 (h2d1.hdp.local) 
   Hostname: h2d1.hdp.local 
   Rack: /default/rack_02 
   Decommission Status : Normal 
   Configured Capacity: 15696052224 (14.62 GB) 
   DFS Used: 314380288 (299.82 MB)
   Non DFS Used: 3238612992 (3.02 GB)
   DFS Remaining: 12143058944 (11.31 GB)
   DFS Used%: 2.00%
   DFS Remaining%: 77.36%
   Configured Cache Capacity: 0 (0 B)
   Cache Used: 0 (0 B)
   Cache Remaining: 0 (0 B)
   Cache Used%: 100.00%
   Cache Remaining%: 0.00%
   Last contact: Thu Jun 12 11:39:51 EDT 2014
   ```

=======
# Configuring HDFS rack awareness

[원문 : hotronworks - Configuring HDFS rack awareness](https://docs.hortonworks.com/HDPDocuments/HDP3/HDP-3.1.0/data-storage/content/improving_performance_with_hdfs_rack_awareness.html)

The NameNode in an HDFS cluster maintains rack IDs of all the DataNodes. The NameNode uses this information about the distribution of DataNodes among various racks in the cluster to select the closer DataNodes for effective block placement during read/write operations. This concept of selecting the closer DataNodes based on their location in the cluster is termed as rack awareness. Rack awareness helps in maintaining fault tolerance in the event of a failure.



## 1. Create a rack topology script

HDFS는 노드들의 Rack location 정보를 결정하기 위해 executable topology script와 topology data file을 이용한다.

**Steps**

1. Executable topology script 와 topology data file을 생성한다.

   ex) example topology script ```rack-topology.sh```

   ```shell
   #!/bin/bash
   # Adjust/Add the property "net.topology.script.file.name"
   # to core-site.xml with the "absolute" path the this
   # file. ENSURE the file is "executable".

   # Supply appropriate rack prefix
   RACK_PREFIX=default

   # To test, supply a hostname as script input:
   if [ $# -gt 0 ]; then

   CTL_FILE=${CTL_FILE:-"rack_topology.data"}
   HADOOP_CONF=${HADOOP_CONF:-"/etc/hadoop/conf"} 

   if [ ! -f ${HADOOP_CONF}/${CTL_FILE} ]; then
    echo -n "/$RACK_PREFIX/rack "
    exit 0
   fi

   while [ $# -gt 0 ] ; do
    nodeArg=$1
    exec< ${HADOOP_CONF}/${CTL_FILE}
    result=""
    while read line ; do
    ar=( $line )
    if [ "${ar[0]}" = "$nodeArg" ] ; then
    result="${ar[1]}"
    fi
    done
    shift
    if [ -z "$result" ] ; then
    echo -n "/$RACK_PREFIX/rack "
    else
    echo -n "/$RACK_PREFIX/rack_$result "
    fi
   done

   else
    echo -n "/$RACK_PREFIX/rack "
   fi
   ```
   example topology data file ```rack_topology.data```  (hostname으로 사용하면 안되고 반드시 IP를 적을 것)

   ```shell
   # This file should be:
   # - Placed in the /etc/hadoop/conf directory
   # - On the Namenode (and backups IE: HA, Failover, etc)
   # - On the Job Tracker OR Resource Manager (and any Failover JT's/RM's) 
   # This file should be placed in the /etc/hadoop/conf directory.

   # Add Hostnames to this file. Format <host ip> <rack_location>
   192.168.2.10 01
   192.168.2.11 02
   192.168.2.12 03
   ```

2. Topology script 와 data file을 모든 클러스터 노드의 ```/etc/hadoop/conf``` 디렉토리에 복사

3. Topology script를 실행해서 올바른 Rack 정보가 return 되는지 확인

   ```shell
   $./rack-topology.sh 192.168.2.10
   /default/rack_01
   ```



## 2. Add the topology script property to core-site.xml

**Steps**

1. HDFS 클러스터를 중지한다.

2. topology script 파일 정보를 ```core-site.xml``` 에 추가한다.

   ```xml
   <property>
     <name>net.topology.script.file.name</name> 
     <value>/etc/hadoop/conf/rack-topology.sh</value>
   </property>
   ```

   By default, the topology script processes up to 100 requests per invocation. You can specify a number other than the default value with the ```net.topology.script.number.args``` property, as shown in the following example:

   ```xml
   <property> 
     <name>net.topology.script.number.args</name> 
     <value>75</value>
   </property>
   ```

## 3. Restart HDFS and MapReduce services

Topology script 정보를 ```core-site.xml``` 에 추가한 뒤에는 HDFS와 MapReduce 서비스를 재시작해야한다.



## 4. Verify rack awareness

Rack awareness가 동작하는지 확인할 필요가 있다.

**Steps**

1. `/var/log/hadoop/hdfs/` 의 NameNode 로그를 확인한다.

   ```
   014-01-13 15:58:08,495 INFO org.apache.hadoop.net.NetworkTopology: Adding
                           a new node: /rack01/<ipaddress>
   ```

2. `hdfs fsck ` 명령으로 확인 (Number of racks)

   ```
   Status: HEALTHY  
   Total size: 123456789 B  
   Total dirs: 0  
   Total files: 1  
   Total blocks (validated): 1 (avg. block size 123456789 B)
   Minimally replicated blocks: 1 (100.0 %)  
   Over-replicated blocks: 0 (0.0 %)  
   Under-replicated blocks: 0 (0.0 %)  
   Mis-replicated blocks: 0 (0.0 %)
   Default replication factor: 3  
   Average block replication: 3.0  
   Corrupt blocks: 0  
   Missing replicas: 0 (0.0 %)  
   Number of data-nodes: 40  
   Number of racks: 2  
   FSCK ended at Mon Jan 13 17:10:51 UTC 2014 in 1 milliseconds
   ```

3. `hdfs dfsadmin -report` 명령으로 각 데이터노드가 Rack 정보를 가지는지 확인

   ```shell
   Configured Capacity: 19010409390080 (17.29 TB)
   Present Capacity: 18228294160384 (16.58 TB)
   DFS Remaining: 5514620928000 (5.02 TB) DFS
   Used: 12713673232384 (11.56 TB)
   DFS Used%: 69.75%
   Under replicated blocks: 181 
   Blocks with corrupt replicas: 0  
   Missing blocks: 0
   -------------------------------------------------  
   Datanodes available: 5 (5 total, 0 dead)  
   Name: 192.168.90.231:50010 (h2d1.hdp.local) 
   Hostname: h2d1.hdp.local 
   Rack: /default/rack_02 
   Decommission Status : Normal 
   Configured Capacity: 15696052224 (14.62 GB) 
   DFS Used: 314380288 (299.82 MB)
   Non DFS Used: 3238612992 (3.02 GB)
   DFS Remaining: 12143058944 (11.31 GB)
   DFS Used%: 2.00%
   DFS Remaining%: 77.36%
   Configured Cache Capacity: 0 (0 B)
   Cache Used: 0 (0 B)
   Cache Remaining: 0 (0 B)
   Cache Used%: 100.00%
   Cache Remaining%: 0.00%
   Last contact: Thu Jun 12 11:39:51 EDT 2014
   ```

>>>>>>> f5b9a9af7ae9ce88850e29199e8d20d1c9829234
