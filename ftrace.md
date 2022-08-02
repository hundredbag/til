# ftrace

```shell
#사용하는 함수들 tracing 방법
# directory : /sys/kernel/debug/tracing
# debug dir 확인하는 명령이 따로 있는것같음.

echo function > current_tracer

echo 1 > tracing_on

echo 0 > tracing_on

vi trace # trace file 확인

echo nop > current_tracer
```

