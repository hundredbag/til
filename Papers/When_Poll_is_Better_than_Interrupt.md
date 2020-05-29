# When Poll is Better than Interrupt

> 참고 <https://events.static.linuxfound.org/sites/events/files/slides/lemoal-nvme-polling-vault-2017-final_0.pdf>

- FAST '12
- Authors: Jisoo Yang, Dave B. Minturn, and Frank Hady, *Intel Corporation*



## Introduction





## Background

- **SSD 및 NVM 기술**의 발전으로 인하여 **mass-storage와 memory의 performance gap이 크게 감소**함
  - I/O 수행시간이 a few microseconds 로 줄어듦의 영향
    - I/O stack time을 무시할 수 없음
    - Big, sequential, batched I/O 과 small, random I/O의 성능 차이 감소

- Traditional block I/O architecture 의 역할
  - I/O requests scheduling 및 I/O 요청을 block device driver로 전달
    - Kernel I/O request 들을 Kernel I/O queue 에 queueing
    - I/O-issuing thread를 I/O wait state로 두어 스케쥴링을 수행
    - 참고 : <http://esos.hanyang.ac.kr/tc/2015gradproject8/i/entry/6>
  - I/O 명령이 완료되면 Device 는 hardware interrupt 를 발생시켜 I/O가 완료되었음을 알림
  - Device driver의 interrupt service routine은 Block I/O subsystem에 알림을 보냄
  - Target memroy를 해제하고 요청의 완료를 기다리는 쓰레드를 un-block 하여 I/O request를 끝냄
  - Storage device는 multiple device command를 자체적인 device queue를 이용해 동시에 처리할 수 있고, 여러 인터럽트를 결합함으로써 오버헤드를 줄일 수 있음.

  ​

- **Traditional block I/O subsystem의 특징**

  - **Asynchronous I/O completion model**
    - Storage device가 I/O를 처리하는 동안 CPU cycle을 다른 작업을 위해 사용할 수 있음
    - I/O 명령이 완료되면 Device 는 hardware interrupt 를 발생시켜 I/O가 완료되었음을 알림
    - Original process는 그 뒤 깨어나서 실행을 재개함
  - I/O scheduler는 **kernel I/O requests를 reorder, combine** 하여 **storage 활용률을 높임**



## Synchronous I/O completion model

### Synchronous I/O model

* I/O 요청을 처리하는 kernel's entire path 가 I/O를 시작한 process context 내에 유지되는 것을 의미
* **CPU poll the device for completion**
* **Polling**은 spin loop를 통해 구현됨 **(대기 중에 CPU 자원을 계속 사용함)**
* Async I/O model에 비해 I/O를 처리하기 위해 커널이 사용하는 CPU cycle을 줄일 수 있음
  * CPU cycle 감소의 원인 : Shortened kernel path, Removal of interrup handling
  * Polling이 extra clock cycle을 사용하는 overhead 발생



### Prototype hardware and device driver

* **NVMe interface 프로토타입으로 시스템에 연결된 DRAM-based 프로토타입**을 사용하였음
  * PCIe * Gen2 bus with eight lanes
  * Device-based DMA engine handling data transfer
  * Device는 segment of main memory로 device driver과 통신함 (commands and completion)
* 측정 결과 **Polling 이 Interrupt 에 비해 빠른 성능을 보임**
  * Polling은 Linux의 block I/O infrastructure의 대부분을 bypassing 하도록 구현



### Experimental setup and methodology

* Setup
  * 16 CPU : 8코어(4코어 * 2소켓) CPU & hyperthreading
  * 메모리 12GB
  * Application : fio
  * Async I/O 상황에서 I/O scheduler는 disabled



### Storage stack latency comparison

* 측정하고자 하는 것
  * 각 completion path가 **I/O를 완료하는 데에 걸리는 시간**
  * 각 모델에서 **커널이 소비하는 CPU time**
  * **비동기 I/O를 수행하는 중에 다른 user process가 사용할 수 있는 CPU time**
* 결과
  * Sync I/O model 이 Async I/O model 보다 latency 관점에서 더 빠름 (4KB, 512B random read)
    * Sync I/O의 경우 Spin-wait cost < code-path reduction (결국 total 성능은 좋아짐)
    * Interrupt delivery latency 때문에 Async path의 hardware time이 더 높게 측정
  * d