# io_uring

참고

fio 에서 io_uring polling 테스트하려면 nvme의 io_poll 을 켜줘야함

io_poll을 키려면 poll_queue 값이 양수값으로 세팅되어야하는데 그냥 세팅해줘서는 io_poll을 켤 수 없음



부팅 시 파라미터를 주기 위해서 grub 파일에



/etc/default/grub 파일에 GRUB_CMDLINE_LINUX_DEFAULT 의 따옴표 안에 nvme.poll_queues=X 라고 값을 설정하고 update-grub 한뒤 부팅하면



poll_queue 값과 io_poll 모두 세팅 되어서 부팅 됨.

자세한건 심사 끝나고 정리.

