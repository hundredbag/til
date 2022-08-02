# Perf 

**Perf** is a **profiler tool for Linux 2.6+ based systems** that abstracts away CPU hardware differences in Linux performance measurements and presents a simple commandline interface. 

Perf is based on the `perf_events` interface exported by recent versions of the Linux kernel.



## Perf commands

### record

The `perf` tool can be used to collect profiles on per-thread, per-process and per-cpu basis.



### stat

* For any of the supported events, **perf can keep a running count during process execution.** In counting modes, the occurrences of events are simply aggregated and presented on standard output at the end of an application run. To generate these statistics, use the `stat` command of `perf`.
* cycle, cache-misses, instructions, page-faults ...

## Perf options

* ​

* -F : To specify a custom rate, it is necessary to use the `-F` option. For instance, to sample on event `instructions` only at the user level and

  ```
  at an average rate of 250 samples/sec:
  perf record -e instructions:u -F 250 ./noploop 4

  [ perf record: Woken up 1 times to write data ]
  [ perf record: Captured and wrote 0.049 MB perf.data (~2160 samples) ]
  ```