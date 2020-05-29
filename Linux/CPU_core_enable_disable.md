# [Linux] How to enable/disable CPU core

I learned from [page1](http://www.upubuntu.com/2011/09/how-to-disable-cpu-core-on-ubuntudebian.html), [page2](https://woorilife.tistory.com/55), [page3](https://www.cyberciti.biz/faq/debian-rhel-centos-redhat-suse-hotplug-cpu/)

### How to check current CPUs and cores

- To see a list of all online CPUs

  ```
  # cat /sys/devices/system/cpu/online
  0-47
  ```

- To see a list of all offline CPUs

  ```
  # cat /sys/devices/system/cpu/offline

  ```

- To see CPU architecture information
  (`On-line CPU(s) list` shows the online cpu numbers)

  ```
  # lscpu
  Architecture:          x86_64
  CPU op-mode(s):        32-bit, 64-bit
  Byte Order:            Little Endian
  CPU(s):                48
  On-line CPU(s) list:   0-47
  Thread(s) per core:    2
  Core(s) per socket:    12
  Socket(s):             2
  NUMA node(s):          2
  Vendor ID:             GenuineIntel
  CPU family:            6
  Model:                 63
  Model name:            Intel(R) Xeon(R) CPU E5-2670 v3 @ 2.30GHz
  Stepping:              2
  CPU MHz:               1199.655
  CPU max MHz:           3100.0000
  CPU min MHz:           1200.0000
  BogoMIPS:              4590.82
  Virtualization:        VT-x
  L1d cache:             32K
  L1i cache:             32K
  L2 cache:              256K
  L3 cache:              30720K
  NUMA node0 CPU(s):     0-11,24-35
  NUMA node1 CPU(s):     12-23,36-47
  ```

### How to disable a CPU core

- Logically turn off (offline) CPU#12 (Restored after reboot)

  ```
  # echo 0 > /sys/devices/system/cpu/cpu12/online
  ```

  or

  ```
  # chcpu -d 12
  CPU 12 disabled
  ```

- Result (```On-line CPU(s) list```, `Off-line CPU(s) list`)

  ```
  # lscpu
  Architecture:          x86_64
  CPU op-mode(s):        32-bit, 64-bit
  Byte Order:            Little Endian
  CPU(s):                48
  On-line CPU(s) list:   0-11,13-47
  Off-line CPU(s) list:  12
  Thread(s) per core:    1
  Core(s) per socket:    12
  Socket(s):             2
  NUMA node(s):          2
  Vendor ID:             GenuineIntel
  CPU family:            6
  Model:                 63
  Model name:            Intel(R) Xeon(R) CPU E5-2670 v3 @ 2.30GHz
  Stepping:              2
  CPU MHz:               1200.057
  CPU max MHz:           3100.0000
  CPU min MHz:           1200.0000
  BogoMIPS:              4590.82
  Virtualization:        VT-x
  L1d cache:             32K
  L1i cache:             32K
  L2 cache:              256K
  L3 cache:              30720K
  NUMA node0 CPU(s):     0-11,24-35
  NUMA node1 CPU(s):     13-23,36-47

  # cat /sys/devices/system/cpu/online
  0-11,13-47

  # cat /sys/devices/system/cpu/offline
  12
  ```

- Logically turn on (online) CPU#12

  ```
  # echo 1 > /sys/devices/system/cpu/cpu12/online
  ```

  or

  ```
  # chcpu -e 12
  CPU 12 enabled
  ```

  ```shell
  for i in `seq 1 5`; do sudo chcpu -e $i; done​
  ```

- 영구적으로 CPU core 갯수를 조절하려면 `/etc/grub.conf`의 kernel 부분에서 maxcpus=N 옵션을 줘야함